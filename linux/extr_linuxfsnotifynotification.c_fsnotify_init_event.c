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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct fsnotify_event {int /*<<< orphan*/  mask; struct inode* inode; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void fsnotify_init_event(struct fsnotify_event *event, struct inode *inode,
			 u32 mask)
{
	INIT_LIST_HEAD(&event->list);
	event->inode = inode;
	event->mask = mask;
}