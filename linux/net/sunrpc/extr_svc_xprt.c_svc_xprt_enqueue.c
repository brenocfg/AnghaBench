#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_xprt {TYPE_2__* xpt_server; int /*<<< orphan*/  xpt_flags; } ;
struct TYPE_4__ {TYPE_1__* sv_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* svo_enqueue_xprt ) (struct svc_xprt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_BUSY ; 
 int /*<<< orphan*/  stub1 (struct svc_xprt*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void svc_xprt_enqueue(struct svc_xprt *xprt)
{
	if (test_bit(XPT_BUSY, &xprt->xpt_flags))
		return;
	xprt->xpt_server->sv_ops->svo_enqueue_xprt(xprt);
}