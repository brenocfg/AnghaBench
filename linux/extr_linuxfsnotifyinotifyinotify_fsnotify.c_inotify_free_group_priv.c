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
struct TYPE_2__ {scalar_t__ ucounts; int /*<<< orphan*/  idr; } ;
struct fsnotify_group {TYPE_1__ inotify_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_inotify_instances (scalar_t__) ; 
 int /*<<< orphan*/  idr_callback ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fsnotify_group*) ; 

__attribute__((used)) static void inotify_free_group_priv(struct fsnotify_group *group)
{
	/* ideally the idr is empty and we won't hit the BUG in the callback */
	idr_for_each(&group->inotify_data.idr, idr_callback, group);
	idr_destroy(&group->inotify_data.idr);
	if (group->inotify_data.ucounts)
		dec_inotify_instances(group->inotify_data.ucounts);
}