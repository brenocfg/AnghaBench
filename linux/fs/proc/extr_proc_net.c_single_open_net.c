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
struct proc_dir_entry {int /*<<< orphan*/  single_show; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct proc_dir_entry* PDE (struct inode*) ; 
 struct net* get_proc_net (struct inode*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct net*) ; 

__attribute__((used)) static int single_open_net(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *de = PDE(inode);
	struct net *net;
	int err;

	net = get_proc_net(inode);
	if (!net)
		return -ENXIO;

	err = single_open(file, de->single_show, net);
	if (err)
		put_net(net);
	return err;
}