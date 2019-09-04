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
struct rpc_xprt {int dummy; } ;
struct inode {struct rpc_xprt* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int single_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 

__attribute__((used)) static int
xprt_info_release(struct inode *inode, struct file *filp)
{
	struct rpc_xprt *xprt = inode->i_private;

	xprt_put(xprt);
	return single_release(inode, filp);
}