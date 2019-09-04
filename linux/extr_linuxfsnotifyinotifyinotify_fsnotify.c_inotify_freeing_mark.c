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
struct fsnotify_mark {int dummy; } ;
struct fsnotify_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inotify_ignored_and_remove_idr (struct fsnotify_mark*,struct fsnotify_group*) ; 

__attribute__((used)) static void inotify_freeing_mark(struct fsnotify_mark *fsn_mark, struct fsnotify_group *group)
{
	inotify_ignored_and_remove_idr(fsn_mark, group);
}