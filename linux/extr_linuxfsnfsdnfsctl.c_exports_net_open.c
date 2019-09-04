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
struct seq_file {int /*<<< orphan*/  private; } ;
struct nfsd_net {int /*<<< orphan*/  svc_export_cache; } ;
struct net {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_exports_op ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int seq_open (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exports_net_open(struct net *net, struct file *file)
{
	int err;
	struct seq_file *seq;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	err = seq_open(file, &nfs_exports_op);
	if (err)
		return err;

	seq = file->private_data;
	seq->private = nn->svc_export_cache;
	return 0;
}