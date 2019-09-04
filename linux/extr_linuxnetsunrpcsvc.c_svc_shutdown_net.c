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
struct svc_serv {TYPE_1__* sv_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* svo_shutdown ) (struct svc_serv*,struct net*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct svc_serv*,struct net*) ; 
 int /*<<< orphan*/  svc_close_net (struct svc_serv*,struct net*) ; 

void svc_shutdown_net(struct svc_serv *serv, struct net *net)
{
	svc_close_net(serv, net);

	if (serv->sv_ops->svo_shutdown)
		serv->sv_ops->svo_shutdown(serv, net);
}