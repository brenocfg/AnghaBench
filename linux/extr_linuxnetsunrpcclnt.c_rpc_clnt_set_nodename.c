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
struct rpc_clnt {int /*<<< orphan*/  cl_nodename; int /*<<< orphan*/  cl_nodelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void rpc_clnt_set_nodename(struct rpc_clnt *clnt, const char *nodename)
{
	clnt->cl_nodelen = strlcpy(clnt->cl_nodename,
			nodename, sizeof(clnt->cl_nodename));
}