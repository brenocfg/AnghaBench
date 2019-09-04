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
struct TYPE_2__ {int /*<<< orphan*/  root; } ;
struct kernfs_node {int /*<<< orphan*/ * priv; int /*<<< orphan*/ * ns; TYPE_1__ dir; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kernfs_node* ERR_PTR (int) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  KERNFS_DIR ; 
 int /*<<< orphan*/  KERNFS_EMPTY_DIR ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int kernfs_add_one (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_new_node (struct kernfs_node*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 

struct kernfs_node *kernfs_create_empty_dir(struct kernfs_node *parent,
					    const char *name)
{
	struct kernfs_node *kn;
	int rc;

	/* allocate */
	kn = kernfs_new_node(parent, name, S_IRUGO|S_IXUGO|S_IFDIR,
			     GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, KERNFS_DIR);
	if (!kn)
		return ERR_PTR(-ENOMEM);

	kn->flags |= KERNFS_EMPTY_DIR;
	kn->dir.root = parent->dir.root;
	kn->ns = NULL;
	kn->priv = NULL;

	/* link in */
	rc = kernfs_add_one(kn);
	if (!rc)
		return kn;

	kernfs_put(kn);
	return ERR_PTR(rc);
}