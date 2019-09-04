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
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 struct kernfs_node* kernfs_find_ns (struct kernfs_node*,char const*,void const*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct kernfs_node *kernfs_find_and_get_ns(struct kernfs_node *parent,
					   const char *name, const void *ns)
{
	struct kernfs_node *kn;

	mutex_lock(&kernfs_mutex);
	kn = kernfs_find_ns(parent, name, ns);
	kernfs_get(kn);
	mutex_unlock(&kernfs_mutex);

	return kn;
}