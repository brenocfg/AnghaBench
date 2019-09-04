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
struct seq_file {int dummy; } ;
struct kernfs_root {int dummy; } ;
struct kernfs_node {int dummy; } ;
struct cgroup_root {int dummy; } ;
struct cgroup {int /*<<< orphan*/  kn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PATH_MAX ; 
 struct cgroup_root* cgroup_root_from_kf (struct kernfs_root*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 struct cgroup* current_cgns_cgroup_from_root (struct cgroup_root*) ; 
 int kernfs_path_from_node (struct kernfs_node*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_escape (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int cgroup_show_path(struct seq_file *sf, struct kernfs_node *kf_node,
		     struct kernfs_root *kf_root)
{
	int len = 0;
	char *buf = NULL;
	struct cgroup_root *kf_cgroot = cgroup_root_from_kf(kf_root);
	struct cgroup *ns_cgroup;

	buf = kmalloc(PATH_MAX, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	spin_lock_irq(&css_set_lock);
	ns_cgroup = current_cgns_cgroup_from_root(kf_cgroot);
	len = kernfs_path_from_node(kf_node, ns_cgroup->kn, buf, PATH_MAX);
	spin_unlock_irq(&css_set_lock);

	if (len >= PATH_MAX)
		len = -ERANGE;
	else if (len > 0) {
		seq_escape(sf, buf, " \t\n\\");
		len = 0;
	}
	kfree(buf);
	return len;
}