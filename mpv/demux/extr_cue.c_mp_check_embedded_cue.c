#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cue_file {int num_tracks; TYPE_1__* tracks; } ;
struct TYPE_2__ {char* filename; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

int mp_check_embedded_cue(struct cue_file *f)
{
    char *fn0 = f->tracks[0].filename;
    for (int n = 1; n < f->num_tracks; n++) {
        char *fn = f->tracks[n].filename;
        // both filenames have the same address (including NULL)
        if (fn0 == fn)
            continue;
        // only one filename is NULL, or the strings don't match
        if (!fn0 || !fn || strcmp(fn0, fn) != 0)
            return -1;
    }
    return 0;
}