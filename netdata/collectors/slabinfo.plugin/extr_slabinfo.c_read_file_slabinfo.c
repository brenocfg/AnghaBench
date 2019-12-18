#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct slabinfo {int active_objs; int num_objs; int obj_size; long pages_per_slab; int data_num_slabs; void* mem_usage; int obj_filling; void* mem_waste; void* data_shared_avail; void* data_active_slabs; void* tune_shared_factor; void* tune_batchcnt; void* tune_limit; void* obj_per_slab; } ;
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 int /*<<< orphan*/  PLUGIN_SLABINFO_PROCFILE ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct slabinfo* get_slabstruct (char*) ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,size_t,int) ; 
 int procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_reopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabdebug (char*,...) ; 
 struct slabinfo* slabinfo_root ; 
 void* str2uint64_t (char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct slabinfo *read_file_slabinfo() {

    slabdebug("-> Reading procfile %s", PLUGIN_SLABINFO_PROCFILE);

    static procfile *ff = NULL;
	static long slab_pagesize = 0;

	if (unlikely(!slab_pagesize)) {
		slab_pagesize = sysconf(_SC_PAGESIZE);
		slabdebug("   Discovered pagesize: %ld", slab_pagesize);
	}

    if(unlikely(!ff)) {
        ff = procfile_reopen(ff, PLUGIN_SLABINFO_PROCFILE, " ,:" , PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff)) {
            error("<- Cannot open file '%s", PLUGIN_SLABINFO_PROCFILE);
            exit(1);
        }
    }

    ff = procfile_readall(ff);
    if(unlikely(!ff)) {
        error("<- Cannot read file '%s'", PLUGIN_SLABINFO_PROCFILE);
        exit(0);
    }


    // Iterate on all lines to populate / update the slabinfo struct
    size_t lines = procfile_lines(ff), l;

    slabdebug("   Read %lu lines from procfile", (unsigned long)lines);
    for(l = 2; l < lines; l++) {
        if (unlikely(procfile_linewords(ff, l) < 14)) {
            slabdebug("    Line %lu has only %lu words, skipping", (unsigned long)l, procfile_linewords(ff,l));
            continue;
        }

        char *name = procfile_lineword(ff, l, 0);
        struct slabinfo *s = get_slabstruct(name);

        s->active_objs    = str2uint64_t(procfile_lineword(ff, l, 1));
        s->num_objs       = str2uint64_t(procfile_lineword(ff, l, 2));
        s->obj_size       = str2uint64_t(procfile_lineword(ff, l, 3));
        s->obj_per_slab   = str2uint64_t(procfile_lineword(ff, l, 4));
        s->pages_per_slab = str2uint64_t(procfile_lineword(ff, l, 5));

        s->tune_limit     = str2uint64_t(procfile_lineword(ff, l, 7));
        s->tune_batchcnt  = str2uint64_t(procfile_lineword(ff, l, 8));
        s->tune_shared_factor = str2uint64_t(procfile_lineword(ff, l, 9));

        s->data_active_slabs = str2uint64_t(procfile_lineword(ff, l, 11));
        s->data_num_slabs    = str2uint64_t(procfile_lineword(ff, l, 12));
        s->data_shared_avail = str2uint64_t(procfile_lineword(ff, l, 13));

        uint32_t memperslab = s->pages_per_slab * slab_pagesize;
        // Internal fragmentation: loss per slab, due to objects not being a multiple of pagesize
        //uint32_t lossperslab = memperslab - s->obj_per_slab * s->obj_size;

        // Total usage = slabs * pages per slab * page size
        s->mem_usage = (uint64_t)(s->data_num_slabs * memperslab);

        // Wasted memory (filling): slabs allocated but not filled: sum total slab - sum total objects
        s->mem_waste = s->mem_usage - (uint64_t)(s->active_objs * s->obj_size);
        //if (s->data_num_slabs > 1)
        //    s->mem_waste += s->data_num_slabs * lossperslab;


        // Slab filling efficiency
        if (s->num_objs > 0)
            s->obj_filling = 100 * s->active_objs / s->num_objs;
        else
            s->obj_filling = 0;

        slabdebug("    Updated slab %s: %lu %lu %lu %lu %lu / %lu %lu %lu / %lu %lu %lu / %lu %lu %hhu",
            name, s->active_objs, s->num_objs, s->obj_size, s->obj_per_slab, s->pages_per_slab,
            s->tune_limit, s->tune_batchcnt, s->tune_shared_factor,
            s->data_active_slabs, s->data_num_slabs, s->data_shared_avail,
            s->mem_usage, s->mem_waste, s->obj_filling);
    }

    return slabinfo_root;
}