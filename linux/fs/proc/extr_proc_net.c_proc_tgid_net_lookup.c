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
struct net {int /*<<< orphan*/  proc_net; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct net* get_proc_task_net (struct inode*) ; 
 struct dentry* proc_lookup_de (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 

__attribute__((used)) static struct dentry *proc_tgid_net_lookup(struct inode *dir,
		struct dentry *dentry, unsigned int flags)
{
	struct dentry *de;
	struct net *net;

	de = ERR_PTR(-ENOENT);
	net = get_proc_task_net(dir);
	if (net != NULL) {
		de = proc_lookup_de(dir, dentry, net->proc_net);
		put_net(net);
	}
	return de;
}