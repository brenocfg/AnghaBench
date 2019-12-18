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
struct tc_ratespec {scalar_t__ rate; scalar_t__ cell_log; int /*<<< orphan*/  linklayer; } ;
struct qdisc_rate_table {int refcnt; struct qdisc_rate_table* next; struct tc_ratespec data; struct tc_ratespec rate; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TC_LINKLAYER_UNAWARE ; 
 scalar_t__ TC_RTAB_SIZE ; 
 int /*<<< orphan*/  __detect_linklayer (struct tc_ratespec*,struct tc_ratespec) ; 
 struct qdisc_rate_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (struct tc_ratespec*,struct tc_ratespec*,int) ; 
 int /*<<< orphan*/  memcpy (struct tc_ratespec,struct tc_ratespec*,int) ; 
 struct tc_ratespec* nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 struct qdisc_rate_table* qdisc_rtab_list ; 

struct qdisc_rate_table *qdisc_get_rtab(struct tc_ratespec *r,
					struct nlattr *tab,
					struct netlink_ext_ack *extack)
{
	struct qdisc_rate_table *rtab;

	if (tab == NULL || r->rate == 0 || r->cell_log == 0 ||
	    nla_len(tab) != TC_RTAB_SIZE) {
		NL_SET_ERR_MSG(extack, "Invalid rate table parameters for searching");
		return NULL;
	}

	for (rtab = qdisc_rtab_list; rtab; rtab = rtab->next) {
		if (!memcmp(&rtab->rate, r, sizeof(struct tc_ratespec)) &&
		    !memcmp(&rtab->data, nla_data(tab), 1024)) {
			rtab->refcnt++;
			return rtab;
		}
	}

	rtab = kmalloc(sizeof(*rtab), GFP_KERNEL);
	if (rtab) {
		rtab->rate = *r;
		rtab->refcnt = 1;
		memcpy(rtab->data, nla_data(tab), 1024);
		if (r->linklayer == TC_LINKLAYER_UNAWARE)
			r->linklayer = __detect_linklayer(r, rtab->data);
		rtab->next = qdisc_rtab_list;
		qdisc_rtab_list = rtab;
	} else {
		NL_SET_ERR_MSG(extack, "Failed to allocate new qdisc rate table");
	}
	return rtab;
}