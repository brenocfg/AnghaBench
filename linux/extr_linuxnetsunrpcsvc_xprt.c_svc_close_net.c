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
struct svc_serv {int /*<<< orphan*/  sv_tempsocks; int /*<<< orphan*/  sv_permsocks; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_clean_up_xprts (struct svc_serv*,struct net*) ; 
 scalar_t__ svc_close_list (struct svc_serv*,int /*<<< orphan*/ *,struct net*) ; 

void svc_close_net(struct svc_serv *serv, struct net *net)
{
	int delay = 0;

	while (svc_close_list(serv, &serv->sv_permsocks, net) +
	       svc_close_list(serv, &serv->sv_tempsocks, net)) {

		svc_clean_up_xprts(serv, net);
		msleep(delay++);
	}
}