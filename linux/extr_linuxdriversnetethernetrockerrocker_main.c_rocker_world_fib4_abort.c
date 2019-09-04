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
struct rocker_world_ops {int /*<<< orphan*/  (* fib4_abort ) (struct rocker*) ;} ;
struct rocker {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rocker*) ; 

__attribute__((used)) static void rocker_world_fib4_abort(struct rocker *rocker)
{
	struct rocker_world_ops *wops = rocker->wops;

	if (wops->fib4_abort)
		wops->fib4_abort(rocker);
}