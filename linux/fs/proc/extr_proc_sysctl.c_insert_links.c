#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctl_table_set {int dummy; } ;
struct ctl_table_header {int /*<<< orphan*/  root; int /*<<< orphan*/  ctl_table; int /*<<< orphan*/  parent; struct ctl_table_set* set; } ;
struct TYPE_4__ {int /*<<< orphan*/  nreg; } ;
struct ctl_dir {TYPE_2__ header; } ;
struct TYPE_3__ {struct ctl_table_set default_set; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct ctl_dir*) ; 
 int /*<<< orphan*/  drop_sysctl_table (TYPE_2__*) ; 
 scalar_t__ get_links (struct ctl_dir*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int insert_header (struct ctl_dir*,struct ctl_table_header*) ; 
 int /*<<< orphan*/  kfree (struct ctl_table_header*) ; 
 struct ctl_table_header* new_links (struct ctl_dir*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_lock ; 
 TYPE_1__ sysctl_table_root ; 
 struct ctl_dir* xlate_dir (struct ctl_table_set*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_links(struct ctl_table_header *head)
{
	struct ctl_table_set *root_set = &sysctl_table_root.default_set;
	struct ctl_dir *core_parent = NULL;
	struct ctl_table_header *links;
	int err;

	if (head->set == root_set)
		return 0;

	core_parent = xlate_dir(root_set, head->parent);
	if (IS_ERR(core_parent))
		return 0;

	if (get_links(core_parent, head->ctl_table, head->root))
		return 0;

	core_parent->header.nreg++;
	spin_unlock(&sysctl_lock);

	links = new_links(core_parent, head->ctl_table, head->root);

	spin_lock(&sysctl_lock);
	err = -ENOMEM;
	if (!links)
		goto out;

	err = 0;
	if (get_links(core_parent, head->ctl_table, head->root)) {
		kfree(links);
		goto out;
	}

	err = insert_header(core_parent, links);
	if (err)
		kfree(links);
out:
	drop_sysctl_table(&core_parent->header);
	return err;
}