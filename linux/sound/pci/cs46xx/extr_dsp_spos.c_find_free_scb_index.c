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
struct dsp_spos_instance {int nscb; int scb_highest_frag_index; TYPE_1__* scbs; } ;
struct TYPE_2__ {scalar_t__ deleted; } ;

/* Variables and functions */

__attribute__((used)) static int find_free_scb_index (struct dsp_spos_instance * ins)
{
	int index = ins->nscb, i;

	for (i = ins->scb_highest_frag_index; i < ins->nscb; ++i) {
		if (ins->scbs[i].deleted) {
			index = i;
			break;
		}
	}

	return index;
}