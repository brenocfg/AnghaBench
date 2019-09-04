#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsnotify_mark {struct fsnotify_group* group; } ;
struct fsnotify_group {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_mark ) (struct fsnotify_mark*) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  fsnotify_put_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  stub1 (struct fsnotify_mark*) ; 

__attribute__((used)) static void fsnotify_final_mark_destroy(struct fsnotify_mark *mark)
{
	struct fsnotify_group *group = mark->group;

	if (WARN_ON_ONCE(!group))
		return;
	group->ops->free_mark(mark);
	fsnotify_put_group(group);
}