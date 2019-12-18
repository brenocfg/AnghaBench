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
struct hist_entry {int /*<<< orphan*/  unfolded; scalar_t__ has_children; } ;

/* Variables and functions */
 char tree__folded_sign (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char hist_entry__folded(const struct hist_entry *he)
{
	return he->has_children ? tree__folded_sign(he->unfolded) : ' ';
}