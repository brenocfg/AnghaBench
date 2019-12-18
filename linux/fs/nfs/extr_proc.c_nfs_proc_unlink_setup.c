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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC_REMOVE ; 
 int /*<<< orphan*/ * nfs_procedures ; 

__attribute__((used)) static void
nfs_proc_unlink_setup(struct rpc_message *msg,
		struct dentry *dentry,
		struct inode *inode)
{
	msg->rpc_proc = &nfs_procedures[NFSPROC_REMOVE];
}