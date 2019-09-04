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
struct svc_serv {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int svc_rpcb_setup (struct svc_serv*,struct net*) ; 
 int /*<<< orphan*/  svc_uses_rpcbind (struct svc_serv*) ; 

int svc_bind(struct svc_serv *serv, struct net *net)
{
	if (!svc_uses_rpcbind(serv))
		return 0;
	return svc_rpcb_setup(serv, net);
}