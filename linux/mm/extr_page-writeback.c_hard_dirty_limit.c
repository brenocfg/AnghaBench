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
struct wb_domain {int /*<<< orphan*/  dirty_limit; } ;

/* Variables and functions */
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long hard_dirty_limit(struct wb_domain *dom,
				      unsigned long thresh)
{
	return max(thresh, dom->dirty_limit);
}