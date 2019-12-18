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
struct file {int dummy; } ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct net* get_proc_task_net (int /*<<< orphan*/ ) ; 
 int proc_readdir_de (struct file*,struct dir_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 

__attribute__((used)) static int proc_tgid_net_readdir(struct file *file, struct dir_context *ctx)
{
	int ret;
	struct net *net;

	ret = -EINVAL;
	net = get_proc_task_net(file_inode(file));
	if (net != NULL) {
		ret = proc_readdir_de(file, ctx, net->proc_net);
		put_net(net);
	}
	return ret;
}