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
struct nfsd_net {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int HEXDIR_LEN ; 
 int /*<<< orphan*/  nfs4_client_to_reclaim (int /*<<< orphan*/ ,struct nfsd_net*) ; 
 int /*<<< orphan*/  printk (char*,struct dentry*) ; 

__attribute__((used)) static int
load_recdir(struct dentry *parent, struct dentry *child, struct nfsd_net *nn)
{
	if (child->d_name.len != HEXDIR_LEN - 1) {
		printk("nfsd4: illegal name %pd in recovery directory\n",
				child);
		/* Keep trying; maybe the others are OK: */
		return 0;
	}
	nfs4_client_to_reclaim(child->d_name.name, nn);
	return 0;
}