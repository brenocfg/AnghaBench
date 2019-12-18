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
struct svc_xprt_class {int /*<<< orphan*/  xcl_ops; } ;
struct svc_xprt {int /*<<< orphan*/  xpt_remotebuf; int /*<<< orphan*/  xpt_net; int /*<<< orphan*/  xpt_flags; int /*<<< orphan*/  xpt_lock; int /*<<< orphan*/  xpt_mutex; int /*<<< orphan*/  xpt_users; int /*<<< orphan*/  xpt_deferred; int /*<<< orphan*/  xpt_ready; int /*<<< orphan*/  xpt_list; struct svc_serv* xpt_server; int /*<<< orphan*/  xpt_ref; int /*<<< orphan*/  xpt_ops; struct svc_xprt_class* xpt_class; } ;
struct svc_serv {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XPT_BUSY ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct svc_xprt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void svc_xprt_init(struct net *net, struct svc_xprt_class *xcl,
		   struct svc_xprt *xprt, struct svc_serv *serv)
{
	memset(xprt, 0, sizeof(*xprt));
	xprt->xpt_class = xcl;
	xprt->xpt_ops = xcl->xcl_ops;
	kref_init(&xprt->xpt_ref);
	xprt->xpt_server = serv;
	INIT_LIST_HEAD(&xprt->xpt_list);
	INIT_LIST_HEAD(&xprt->xpt_ready);
	INIT_LIST_HEAD(&xprt->xpt_deferred);
	INIT_LIST_HEAD(&xprt->xpt_users);
	mutex_init(&xprt->xpt_mutex);
	spin_lock_init(&xprt->xpt_lock);
	set_bit(XPT_BUSY, &xprt->xpt_flags);
	xprt->xpt_net = get_net(net);
	strcpy(xprt->xpt_remotebuf, "uninitialized");
}