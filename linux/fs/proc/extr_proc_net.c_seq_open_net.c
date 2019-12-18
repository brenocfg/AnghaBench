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
struct seq_net_private {struct net* net; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;
struct file {int f_mode; } ;
struct TYPE_2__ {unsigned int state_size; int /*<<< orphan*/  seq_ops; int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FMODE_WRITE ; 
 TYPE_1__* PDE (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct seq_net_private* __seq_open_private (struct file*,int /*<<< orphan*/ ,unsigned int) ; 
 struct net* get_proc_net (struct inode*) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 

__attribute__((used)) static int seq_open_net(struct inode *inode, struct file *file)
{
	unsigned int state_size = PDE(inode)->state_size;
	struct seq_net_private *p;
	struct net *net;

	WARN_ON_ONCE(state_size < sizeof(*p));

	if (file->f_mode & FMODE_WRITE && !PDE(inode)->write)
		return -EACCES;

	net = get_proc_net(inode);
	if (!net)
		return -ENXIO;

	p = __seq_open_private(file, PDE(inode)->seq_ops, state_size);
	if (!p) {
		put_net(net);
		return -ENOMEM;
	}
#ifdef CONFIG_NET_NS
	p->net = net;
#endif
	return 0;
}