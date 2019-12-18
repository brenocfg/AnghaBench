#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gcov_node {char* links; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {scalar_t__ ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char debugfs_create_symlink (int /*<<< orphan*/ ,struct dentry*,char*) ; 
 int /*<<< orphan*/  debugfs_remove (char) ; 
 int /*<<< orphan*/  deskew (char const*) ; 
 int /*<<< orphan*/  gcov_info_filename (int /*<<< orphan*/ ) ; 
 TYPE_1__* gcov_link ; 
 char* get_link_target (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_node_info (struct gcov_node*) ; 
 char* kbasename (char*) ; 
 char* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static void add_links(struct gcov_node *node, struct dentry *parent)
{
	const char *basename;
	char *target;
	int num;
	int i;

	for (num = 0; gcov_link[num].ext; num++)
		/* Nothing. */;
	node->links = kcalloc(num, sizeof(struct dentry *), GFP_KERNEL);
	if (!node->links)
		return;
	for (i = 0; i < num; i++) {
		target = get_link_target(
				gcov_info_filename(get_node_info(node)),
				&gcov_link[i]);
		if (!target)
			goto out_err;
		basename = kbasename(target);
		if (basename == target)
			goto out_err;
		node->links[i] = debugfs_create_symlink(deskew(basename),
							parent,	target);
		kfree(target);
	}

	return;
out_err:
	kfree(target);
	while (i-- > 0)
		debugfs_remove(node->links[i]);
	kfree(node->links);
	node->links = NULL;
}