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
struct callchain_list {int unfolded; int /*<<< orphan*/  has_children; } ;

/* Variables and functions */

__attribute__((used)) static bool callchain_list__toggle_fold(struct callchain_list *cl)
{
	if (!cl)
		return false;

	if (!cl->has_children)
		return false;

	cl->unfolded = !cl->unfolded;
	return true;
}