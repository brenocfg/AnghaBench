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
struct aa_ns {struct aa_ns* parent; } ;

/* Variables and functions */

bool aa_ns_visible(struct aa_ns *curr, struct aa_ns *view, bool subns)
{
	if (curr == view)
		return true;

	if (!subns)
		return false;

	for ( ; view; view = view->parent) {
		if (view->parent == curr)
			return true;
	}

	return false;
}