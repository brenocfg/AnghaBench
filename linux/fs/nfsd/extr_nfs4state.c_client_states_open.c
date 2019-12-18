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
struct seq_file {struct nfs4_client* private; } ;
struct nfs4_client {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int ENXIO ; 
 struct nfs4_client* get_nfsdfs_clp (struct inode*) ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  states_seq_ops ; 

__attribute__((used)) static int client_states_open(struct inode *inode, struct file *file)
{
	struct seq_file *s;
	struct nfs4_client *clp;
	int ret;

	clp = get_nfsdfs_clp(inode);
	if (!clp)
		return -ENXIO;

	ret = seq_open(file, &states_seq_ops);
	if (ret)
		return ret;
	s = file->private_data;
	s->private = clp;
	return 0;
}