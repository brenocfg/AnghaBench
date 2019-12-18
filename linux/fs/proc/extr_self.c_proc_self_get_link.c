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
struct pid_namespace {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree_link ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct pid_namespace* proc_pid_ns (struct inode*) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int task_tgid_nr_ns (int /*<<< orphan*/ ,struct pid_namespace*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static const char *proc_self_get_link(struct dentry *dentry,
				      struct inode *inode,
				      struct delayed_call *done)
{
	struct pid_namespace *ns = proc_pid_ns(inode);
	pid_t tgid = task_tgid_nr_ns(current, ns);
	char *name;

	if (!tgid)
		return ERR_PTR(-ENOENT);
	/* max length of unsigned int in decimal + NULL term */
	name = kmalloc(10 + 1, dentry ? GFP_KERNEL : GFP_ATOMIC);
	if (unlikely(!name))
		return dentry ? ERR_PTR(-ENOMEM) : ERR_PTR(-ECHILD);
	sprintf(name, "%u", tgid);
	set_delayed_call(done, kfree_link, name);
	return name;
}