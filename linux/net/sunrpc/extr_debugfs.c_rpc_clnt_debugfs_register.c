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
struct rpc_clnt {int cl_clid; int /*<<< orphan*/  cl_debugfs; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct rpc_clnt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_xprt_debugfs ; 
 int /*<<< orphan*/  rpc_clnt_dir ; 
 int /*<<< orphan*/  rpc_clnt_iterate_for_each_xprt (struct rpc_clnt*,int /*<<< orphan*/ ,int*) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tasks_fops ; 

void
rpc_clnt_debugfs_register(struct rpc_clnt *clnt)
{
	int len;
	char name[9]; /* enough for 8 hex digits + NULL */
	int xprtnum = 0;

	len = snprintf(name, sizeof(name), "%x", clnt->cl_clid);
	if (len >= sizeof(name))
		return;

	/* make the per-client dir */
	clnt->cl_debugfs = debugfs_create_dir(name, rpc_clnt_dir);

	/* make tasks file */
	debugfs_create_file("tasks", S_IFREG | 0400, clnt->cl_debugfs, clnt,
			    &tasks_fops);

	rpc_clnt_iterate_for_each_xprt(clnt, do_xprt_debugfs, &xprtnum);
}