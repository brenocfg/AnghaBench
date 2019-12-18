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
struct kernfs_open_node {int /*<<< orphan*/  files; int /*<<< orphan*/  poll; int /*<<< orphan*/  event; int /*<<< orphan*/  refcnt; } ;
struct kernfs_open_file {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct kernfs_open_node* open; } ;
struct kernfs_node {TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_open_file_mutex ; 
 int /*<<< orphan*/  kernfs_open_node_lock ; 
 int /*<<< orphan*/  kfree (struct kernfs_open_node*) ; 
 struct kernfs_open_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kernfs_get_open_node(struct kernfs_node *kn,
				struct kernfs_open_file *of)
{
	struct kernfs_open_node *on, *new_on = NULL;

 retry:
	mutex_lock(&kernfs_open_file_mutex);
	spin_lock_irq(&kernfs_open_node_lock);

	if (!kn->attr.open && new_on) {
		kn->attr.open = new_on;
		new_on = NULL;
	}

	on = kn->attr.open;
	if (on) {
		atomic_inc(&on->refcnt);
		list_add_tail(&of->list, &on->files);
	}

	spin_unlock_irq(&kernfs_open_node_lock);
	mutex_unlock(&kernfs_open_file_mutex);

	if (on) {
		kfree(new_on);
		return 0;
	}

	/* not there, initialize a new one and retry */
	new_on = kmalloc(sizeof(*new_on), GFP_KERNEL);
	if (!new_on)
		return -ENOMEM;

	atomic_set(&new_on->refcnt, 0);
	atomic_set(&new_on->event, 1);
	init_waitqueue_head(&new_on->poll);
	INIT_LIST_HEAD(&new_on->files);
	goto retry;
}