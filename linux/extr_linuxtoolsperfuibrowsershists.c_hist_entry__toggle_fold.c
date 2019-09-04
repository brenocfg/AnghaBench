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
struct hist_entry {int unfolded; int /*<<< orphan*/  has_children; } ;

/* Variables and functions */

__attribute__((used)) static bool hist_entry__toggle_fold(struct hist_entry *he)
{
	if (!he)
		return false;

	if (!he->has_children)
		return false;

	he->unfolded = !he->unfolded;
	return true;
}