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
struct rblist {scalar_t__ nr_entries; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_ROOT ; 

void rblist__init(struct rblist *rblist)
{
	if (rblist != NULL) {
		rblist->entries	 = RB_ROOT;
		rblist->nr_entries = 0;
	}

	return;
}