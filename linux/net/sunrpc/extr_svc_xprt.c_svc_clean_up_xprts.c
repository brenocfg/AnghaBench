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
struct svc_xprt {int /*<<< orphan*/  xpt_flags; } ;
struct svc_serv {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_delete_xprt (struct svc_xprt*) ; 
 struct svc_xprt* svc_dequeue_net (struct svc_serv*,struct net*) ; 

__attribute__((used)) static void svc_clean_up_xprts(struct svc_serv *serv, struct net *net)
{
	struct svc_xprt *xprt;

	while ((xprt = svc_dequeue_net(serv, net))) {
		set_bit(XPT_CLOSE, &xprt->xpt_flags);
		svc_delete_xprt(xprt);
	}
}