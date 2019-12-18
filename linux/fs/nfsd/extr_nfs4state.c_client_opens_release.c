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
 int /*<<< orphan*/  drop_client (struct nfs4_client*) ; 

__attribute__((used)) static int client_opens_release(struct inode *inode, struct file *file)
{
	struct seq_file *m = file->private_data;
	struct nfs4_client *clp = m->private;

	/* XXX: alternatively, we could get/drop in seq start/stop */
	drop_client(clp);
	return 0;
}