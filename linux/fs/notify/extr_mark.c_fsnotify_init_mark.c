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
struct fsnotify_mark {int /*<<< orphan*/  connector; struct fsnotify_group* group; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; } ;
struct fsnotify_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_get_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  memset (struct fsnotify_mark*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void fsnotify_init_mark(struct fsnotify_mark *mark,
			struct fsnotify_group *group)
{
	memset(mark, 0, sizeof(*mark));
	spin_lock_init(&mark->lock);
	refcount_set(&mark->refcnt, 1);
	fsnotify_get_group(group);
	mark->group = group;
	WRITE_ONCE(mark->connector, NULL);
}