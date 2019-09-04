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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct nfsd4_conn {TYPE_1__ cn_xpt_user; int /*<<< orphan*/  cn_flags; int /*<<< orphan*/  cn_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfsd4_conn* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_xprt_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfsd4_conn *alloc_conn(struct svc_rqst *rqstp, u32 flags)
{
	struct nfsd4_conn *conn;

	conn = kmalloc(sizeof(struct nfsd4_conn), GFP_KERNEL);
	if (!conn)
		return NULL;
	svc_xprt_get(rqstp->rq_xprt);
	conn->cn_xprt = rqstp->rq_xprt;
	conn->cn_flags = flags;
	INIT_LIST_HEAD(&conn->cn_xpt_user.list);
	return conn;
}