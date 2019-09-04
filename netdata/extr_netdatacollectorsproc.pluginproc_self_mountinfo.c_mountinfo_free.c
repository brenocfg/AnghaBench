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
struct mountinfo {struct mountinfo* super_options; struct mountinfo* mount_source; struct mountinfo* filesystem; struct mountinfo* persistent_id; struct mountinfo* mount_options; struct mountinfo* mount_point; struct mountinfo* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (struct mountinfo*) ; 

__attribute__((used)) static void mountinfo_free(struct mountinfo *mi) {
    freez(mi->root);
    freez(mi->mount_point);
    freez(mi->mount_options);
    freez(mi->persistent_id);
/*
    if(mi->optional_fields_count) {
        int i;
        for(i = 0; i < mi->optional_fields_count ; i++)
            free(*mi->optional_fields[i]);
    }
    free(mi->optional_fields);
*/
    freez(mi->filesystem);
    freez(mi->mount_source);
    freez(mi->super_options);
    freez(mi);
}