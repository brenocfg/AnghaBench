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
typedef  struct ip_vs_conn_param {scalar_t__ vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  af; scalar_t__ cport; int /*<<< orphan*/  caddr; int /*<<< orphan*/  protocol; } const ip_vs_conn_param ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct ip_vs_conn* __ip_vs_conn_in_get (struct ip_vs_conn_param const*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_conn_no_cport_cnt ; 
 int /*<<< orphan*/  ip_vs_proto_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 

struct ip_vs_conn *ip_vs_conn_in_get(const struct ip_vs_conn_param *p)
{
	struct ip_vs_conn *cp;

	cp = __ip_vs_conn_in_get(p);
	if (!cp && atomic_read(&ip_vs_conn_no_cport_cnt)) {
		struct ip_vs_conn_param cport_zero_p = *p;
		cport_zero_p.cport = 0;
		cp = __ip_vs_conn_in_get(&cport_zero_p);
	}

	IP_VS_DBG_BUF(9, "lookup/in %s %s:%d->%s:%d %s\n",
		      ip_vs_proto_name(p->protocol),
		      IP_VS_DBG_ADDR(p->af, p->caddr), ntohs(p->cport),
		      IP_VS_DBG_ADDR(p->af, p->vaddr), ntohs(p->vport),
		      cp ? "hit" : "not hit");

	return cp;
}