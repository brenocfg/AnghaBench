#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int count; int magic; char* name; int pos; int /*<<< orphan*/  type; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  FD_FILETYPE ;

/* Variables and functions */
 TYPE_1__* all_files ; 
 int /*<<< orphan*/  all_files_grow () ; 
 int all_files_len ; 
 int all_files_size ; 
 int /*<<< orphan*/  debug_log (char*,...) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 void* file_descriptor_add (TYPE_1__*) ; 
 scalar_t__ file_descriptor_find (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (void*) ; 
 char* strdupz (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int file_descriptor_set_on_empty_slot(const char *name, uint32_t hash, FD_FILETYPE type) {
    // check we have enough memory to add it
    if(!all_files || all_files_len == all_files_size)
        all_files_grow();

    debug_log("  >> searching for empty slot.");

    // search for an empty slot

    static int last_pos = 0;
    int i, c;
    for(i = 0, c = last_pos ; i < all_files_size ; i++, c++) {
        if(c >= all_files_size) c = 0;
        if(c == 0) continue;

        if(!all_files[c].count) {
            debug_log("  >> Examining slot %d.", c);

#ifdef NETDATA_INTERNAL_CHECKS
            if(all_files[c].magic == 0x0BADCAFE && all_files[c].name && file_descriptor_find(all_files[c].name, all_files[c].hash))
                error("fd on position %d is not cleared properly. It still has %s in it.", c, all_files[c].name);
#endif /* NETDATA_INTERNAL_CHECKS */

            debug_log("  >> %s fd position %d for %s (last name: %s)", all_files[c].name?"re-using":"using", c, name, all_files[c].name);

            freez((void *)all_files[c].name);
            all_files[c].name = NULL;
            last_pos = c;
            break;
        }
    }

    all_files_len++;

    if(i == all_files_size) {
        fatal("We should find an empty slot, but there isn't any");
        exit(1);
    }
    // else we have an empty slot in 'c'

    debug_log("  >> updating slot %d.", c);

    all_files[c].name = strdupz(name);
    all_files[c].hash = hash;
    all_files[c].type = type;
    all_files[c].pos  = c;
    all_files[c].count = 1;
#ifdef NETDATA_INTERNAL_CHECKS
    all_files[c].magic = 0x0BADCAFE;
#endif /* NETDATA_INTERNAL_CHECKS */
    if(unlikely(file_descriptor_add(&all_files[c]) != (void *)&all_files[c]))
        error("INTERNAL ERROR: duplicate indexing of fd.");

    debug_log("using fd position %d (name: %s)", c, all_files[c].name);

    return c;
}