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
struct rpc_clnt {int cl_clid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_clids ; 

__attribute__((used)) static int rpc_alloc_clid(struct rpc_clnt *clnt)
{
	int clid;

	clid = ida_simple_get(&rpc_clids, 0, 0, GFP_KERNEL);
	if (clid < 0)
		return clid;
	clnt->cl_clid = clid;
	return 0;
}