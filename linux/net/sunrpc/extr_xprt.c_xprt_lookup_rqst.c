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
struct TYPE_2__ {int /*<<< orphan*/  bad_xids; } ;
struct rpc_xprt {TYPE_1__ stat; } ;
struct rpc_rqst {int /*<<< orphan*/  rq_xtime; int /*<<< orphan*/  rq_rtt; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xprt_lookup_rqst (struct rpc_xprt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rpc_rqst* xprt_request_rb_find (struct rpc_xprt*,int /*<<< orphan*/ ) ; 

struct rpc_rqst *xprt_lookup_rqst(struct rpc_xprt *xprt, __be32 xid)
{
	struct rpc_rqst *entry;

	entry = xprt_request_rb_find(xprt, xid);
	if (entry != NULL) {
		trace_xprt_lookup_rqst(xprt, xid, 0);
		entry->rq_rtt = ktime_sub(ktime_get(), entry->rq_xtime);
		return entry;
	}

	dprintk("RPC:       xprt_lookup_rqst did not find xid %08x\n",
			ntohl(xid));
	trace_xprt_lookup_rqst(xprt, xid, -ENOENT);
	xprt->stat.bad_xids++;
	return NULL;
}