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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct phonetmsg {scalar_t__ pn_msg_id; scalar_t__ pn_e_submsg_id; scalar_t__ pn_submsg_id; } ;
struct phonethdr {scalar_t__ pn_res; } ;

/* Variables and functions */
 scalar_t__ PN_COMMGR ; 
 scalar_t__ PN_COMMON_MESSAGE ; 
 scalar_t__ PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP ; 
 scalar_t__ PN_COMM_SERVICE_NOT_IDENTIFIED_RESP ; 
 scalar_t__ PN_PREFIX ; 
 struct phonethdr* pn_hdr (struct sk_buff*) ; 
 struct phonetmsg* pn_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static inline int can_respond(struct sk_buff *skb)
{
	const struct phonethdr *ph;
	const struct phonetmsg *pm;
	u8 submsg_id;

	if (!pskb_may_pull(skb, 3))
		return 0;

	ph = pn_hdr(skb);
	if (ph->pn_res == PN_PREFIX && !pskb_may_pull(skb, 5))
		return 0;
	if (ph->pn_res == PN_COMMGR) /* indications */
		return 0;

	ph = pn_hdr(skb); /* re-acquires the pointer */
	pm = pn_msg(skb);
	if (pm->pn_msg_id != PN_COMMON_MESSAGE)
		return 1;
	submsg_id = (ph->pn_res == PN_PREFIX)
		? pm->pn_e_submsg_id : pm->pn_submsg_id;
	if (submsg_id != PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP &&
		pm->pn_e_submsg_id != PN_COMM_SERVICE_NOT_IDENTIFIED_RESP)
		return 1;
	return 0;
}