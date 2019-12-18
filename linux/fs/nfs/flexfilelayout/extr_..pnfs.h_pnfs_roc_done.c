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
struct rpc_task {int dummy; } ;
struct nfs4_layoutreturn_res {int dummy; } ;
struct nfs4_layoutreturn_args {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
pnfs_roc_done(struct rpc_task *task, struct inode *inode,
		struct nfs4_layoutreturn_args **argpp,
		struct nfs4_layoutreturn_res **respp,
		int *ret)
{
	return 0;
}