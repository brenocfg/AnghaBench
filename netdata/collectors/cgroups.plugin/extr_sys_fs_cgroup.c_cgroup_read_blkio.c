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
typedef  scalar_t__ uint32_t ;
struct blkio {scalar_t__ enabled; scalar_t__ delay_counter; int updated; scalar_t__ Write; scalar_t__ Read; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  procfile ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_AUTO ; 
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 scalar_t__ Read_hash ; 
 scalar_t__ Write_hash ; 
 scalar_t__ cgroup_recheck_zero_blkio_every_iterations ; 
 int cgroups_check ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ netdata_zero_metrics_enabled ; 
 unsigned long procfile_lines (int /*<<< orphan*/ *) ; 
 char* procfile_lineword (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procfile_reopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_hash (char*) ; 
 scalar_t__ str2ull (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void cgroup_read_blkio(struct blkio *io) {
    if(unlikely(io->enabled == CONFIG_BOOLEAN_AUTO && io->delay_counter > 0)) {
        io->delay_counter--;
        return;
    }

    if(likely(io->filename)) {
        static procfile *ff = NULL;

        ff = procfile_reopen(ff, io->filename, NULL, PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff)) {
            io->updated = 0;
            cgroups_check = 1;
            return;
        }

        ff = procfile_readall(ff);
        if(unlikely(!ff)) {
            io->updated = 0;
            cgroups_check = 1;
            return;
        }

        unsigned long i, lines = procfile_lines(ff);

        if(unlikely(lines < 1)) {
            error("CGROUP: file '%s' should have 1+ lines.", io->filename);
            io->updated = 0;
            return;
        }

        io->Read = 0;
        io->Write = 0;
/*
        io->Sync = 0;
        io->Async = 0;
        io->Total = 0;
*/

        for(i = 0; i < lines ; i++) {
            char *s = procfile_lineword(ff, i, 1);
            uint32_t hash = simple_hash(s);

            if(unlikely(hash == Read_hash && !strcmp(s, "Read")))
                io->Read += str2ull(procfile_lineword(ff, i, 2));

            else if(unlikely(hash == Write_hash && !strcmp(s, "Write")))
                io->Write += str2ull(procfile_lineword(ff, i, 2));

/*
            else if(unlikely(hash == Sync_hash && !strcmp(s, "Sync")))
                io->Sync += str2ull(procfile_lineword(ff, i, 2));

            else if(unlikely(hash == Async_hash && !strcmp(s, "Async")))
                io->Async += str2ull(procfile_lineword(ff, i, 2));

            else if(unlikely(hash == Total_hash && !strcmp(s, "Total")))
                io->Total += str2ull(procfile_lineword(ff, i, 2));
*/
        }

        io->updated = 1;

        if(unlikely(io->enabled == CONFIG_BOOLEAN_AUTO)) {
            if(unlikely(io->Read || io->Write || netdata_zero_metrics_enabled == CONFIG_BOOLEAN_YES))
                io->enabled = CONFIG_BOOLEAN_YES;
            else
                io->delay_counter = cgroup_recheck_zero_blkio_every_iterations;
        }
    }
}