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
typedef  int /*<<< orphan*/  watch ;
struct xenbus_watch {int /*<<< orphan*/  list; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_watch (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watches ; 
 int /*<<< orphan*/  watches_lock ; 
 int xs_watch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xs_watch_rwsem ; 

int register_xenbus_watch(struct xenbus_watch *watch)
{
	/* Pointer in ascii is the token. */
	char token[sizeof(watch) * 2 + 1];
	int err;

	sprintf(token, "%lX", (long)watch);

	down_read(&xs_watch_rwsem);

	spin_lock(&watches_lock);
	BUG_ON(find_watch(token));
	list_add(&watch->list, &watches);
	spin_unlock(&watches_lock);

	err = xs_watch(watch->node, token);

	if (err) {
		spin_lock(&watches_lock);
		list_del(&watch->list);
		spin_unlock(&watches_lock);
	}

	up_read(&xs_watch_rwsem);

	return err;
}