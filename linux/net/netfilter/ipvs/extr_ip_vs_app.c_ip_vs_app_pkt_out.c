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
struct sk_buff {int dummy; } ;
struct ip_vs_iphdr {int dummy; } ;
struct ip_vs_conn {scalar_t__ protocol; struct ip_vs_app* app; } ;
struct ip_vs_app {int (* pkt_out ) (struct ip_vs_app*,struct ip_vs_conn*,struct sk_buff*,int /*<<< orphan*/ *,struct ip_vs_iphdr*) ;} ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int app_tcp_pkt_out (struct ip_vs_conn*,struct sk_buff*,struct ip_vs_app*,struct ip_vs_iphdr*) ; 
 int stub1 (struct ip_vs_app*,struct ip_vs_conn*,struct sk_buff*,int /*<<< orphan*/ *,struct ip_vs_iphdr*) ; 

int ip_vs_app_pkt_out(struct ip_vs_conn *cp, struct sk_buff *skb,
		      struct ip_vs_iphdr *ipvsh)
{
	struct ip_vs_app *app;

	/*
	 *	check if application module is bound to
	 *	this ip_vs_conn.
	 */
	if ((app = cp->app) == NULL)
		return 1;

	/* TCP is complicated */
	if (cp->protocol == IPPROTO_TCP)
		return app_tcp_pkt_out(cp, skb, app, ipvsh);

	/*
	 *	Call private output hook function
	 */
	if (app->pkt_out == NULL)
		return 1;

	return app->pkt_out(app, cp, skb, NULL, ipvsh);
}