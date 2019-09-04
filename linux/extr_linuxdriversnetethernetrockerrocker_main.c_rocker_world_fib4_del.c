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
struct rocker_world_ops {int (* fib4_del ) (struct rocker*,struct fib_entry_notifier_info const*) ;} ;
struct rocker {struct rocker_world_ops* wops; } ;
struct fib_entry_notifier_info {int dummy; } ;

/* Variables and functions */
 int stub1 (struct rocker*,struct fib_entry_notifier_info const*) ; 

__attribute__((used)) static int rocker_world_fib4_del(struct rocker *rocker,
				 const struct fib_entry_notifier_info *fen_info)
{
	struct rocker_world_ops *wops = rocker->wops;

	if (!wops->fib4_del)
		return 0;
	return wops->fib4_del(rocker, fen_info);
}