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
struct super_block {int dummy; } ;
struct rpc_pipe {scalar_t__ dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_unlink (scalar_t__) ; 

__attribute__((used)) static void nfs4blocklayout_unregister_sb(struct super_block *sb,
					  struct rpc_pipe *pipe)
{
	if (pipe->dentry)
		rpc_unlink(pipe->dentry);
}