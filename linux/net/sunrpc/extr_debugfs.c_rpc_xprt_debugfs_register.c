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
struct rpc_xprt {int /*<<< orphan*/  inject_disconnect; int /*<<< orphan*/  debugfs; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int S_IFREG ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct rpc_xprt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_inject_disconnect ; 
 int /*<<< orphan*/  rpc_xprt_dir ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xprt_info_fops ; 

void
rpc_xprt_debugfs_register(struct rpc_xprt *xprt)
{
	int len, id;
	static atomic_t	cur_id;
	char		name[9]; /* 8 hex digits + NULL term */

	id = (unsigned int)atomic_inc_return(&cur_id);

	len = snprintf(name, sizeof(name), "%x", id);
	if (len >= sizeof(name))
		return;

	/* make the per-client dir */
	xprt->debugfs = debugfs_create_dir(name, rpc_xprt_dir);

	/* make tasks file */
	debugfs_create_file("info", S_IFREG | 0400, xprt->debugfs, xprt,
			    &xprt_info_fops);

	atomic_set(&xprt->inject_disconnect, rpc_inject_disconnect);
}