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
struct wa_rpipe {int /*<<< orphan*/  seg_list; int /*<<< orphan*/  segs_available; } ;

/* Variables and functions */
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int rpipe_avail_inc(struct wa_rpipe *rpipe)
{
	return atomic_inc_return(&rpipe->segs_available) > 0
		&& !list_empty(&rpipe->seg_list);
}