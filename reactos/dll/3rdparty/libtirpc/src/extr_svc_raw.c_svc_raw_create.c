#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  oa_base; } ;
struct TYPE_7__ {TYPE_1__ xp_verf; int /*<<< orphan*/ * xp_p3; scalar_t__ xp_port; int /*<<< orphan*/  xp_fd; } ;
struct svc_raw_private {TYPE_2__ server; int /*<<< orphan*/ * raw_buf; int /*<<< orphan*/  xdr_stream; int /*<<< orphan*/  verf_body; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SETSIZE ; 
 int UDPMSGSIZE ; 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/ * __rpc_rawcombuf ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_raw_ops (TYPE_2__*) ; 
 struct svc_raw_private* svc_raw_private ; 
 int /*<<< orphan*/  svcraw_lock ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_register (TYPE_2__*) ; 

SVCXPRT *
svc_raw_create()
{
	struct svc_raw_private *srp;
/* VARIABLES PROTECTED BY svcraw_lock: svc_raw_private, srp */

	mutex_lock(&svcraw_lock);
	srp = svc_raw_private;
	if (srp == NULL) {
		srp = (struct svc_raw_private *)calloc(1, sizeof (*srp));
		if (srp == NULL) {
			mutex_unlock(&svcraw_lock);
			return (NULL);
		}
		if (__rpc_rawcombuf == NULL)
			__rpc_rawcombuf = calloc(UDPMSGSIZE, sizeof (char));
		srp->raw_buf = __rpc_rawcombuf; /* Share it with the client */
		svc_raw_private = srp;
	}
	srp->server.xp_fd = FD_SETSIZE;
	srp->server.xp_port = 0;
	srp->server.xp_p3 = NULL;
	svc_raw_ops(&srp->server);
	srp->server.xp_verf.oa_base = srp->verf_body;
	xdrmem_create(&srp->xdr_stream, srp->raw_buf, UDPMSGSIZE, XDR_DECODE);
	xprt_register(&srp->server);
	mutex_unlock(&svcraw_lock);
	return (&srp->server);
}