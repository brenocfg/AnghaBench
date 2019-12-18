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
typedef  scalar_t__ const hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static int is_in_nid_list(hda_nid_t nid, const hda_nid_t *list)
{
	for (; *list; list++)
		if (*list == nid)
			return 1;
	return 0;
}