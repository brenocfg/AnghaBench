#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zip_uint64_t ;
struct zip {scalar_t__ ch_flags; scalar_t__ flags; size_t nentry; TYPE_2__* entry; scalar_t__ comment_changed; } ;
struct TYPE_4__ {scalar_t__ deleted; TYPE_1__* changes; scalar_t__ source; } ;
struct TYPE_3__ {scalar_t__ changed; } ;

/* Variables and functions */

int
_zip_changed(const struct zip *za, zip_uint64_t *survivorsp)
{
    int changed;
    zip_uint64_t i, survivors;

    changed = 0;
    survivors = 0;

    if (za->comment_changed || za->ch_flags != za->flags)
	changed = 1;

    for (i=0; i<za->nentry; i++) {
	if (za->entry[i].deleted || za->entry[i].source || (za->entry[i].changes && za->entry[i].changes->changed != 0))
	    changed = 1;
	if (!za->entry[i].deleted)
	    survivors++;
    }

    if (survivorsp)
	*survivorsp = survivors;

    return changed;
}