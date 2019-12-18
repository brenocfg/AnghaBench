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
union l2tp_val {scalar_t__ val32; } ;
typedef  scalar_t__ u16 ;
struct xt_l2tp_info {int dummy; } ;
struct xt_action_param {struct xt_l2tp_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct l2tp_data {int version; int /*<<< orphan*/  type; void* sid; void* tid; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  lhbuf ;

/* Variables and functions */
 int /*<<< orphan*/  XT_L2TP_TYPE_CONTROL ; 
 int /*<<< orphan*/  XT_L2TP_TYPE_DATA ; 
 int l2tp_match (struct xt_l2tp_info const*,struct l2tp_data*) ; 
 void* ntohl (scalar_t__) ; 
 union l2tp_val* skb_header_pointer (struct sk_buff const*,scalar_t__,int,union l2tp_val*) ; 

__attribute__((used)) static bool l2tp_ip_mt(const struct sk_buff *skb, struct xt_action_param *par, u16 thoff)
{
	const struct xt_l2tp_info *info = par->matchinfo;
	union l2tp_val *lh;
	union l2tp_val lhbuf;
	struct l2tp_data data = { 0, };

	/* For IP encap, the L2TP sid is the first 32-bits. */
	lh = skb_header_pointer(skb, thoff, sizeof(lhbuf), &lhbuf);
	if (lh == NULL)
		return false;
	if (lh->val32 == 0) {
		/* Must be a control packet. The L2TP tid is further
		 * into the packet.
		 */
		data.type = XT_L2TP_TYPE_CONTROL;
		lh = skb_header_pointer(skb, thoff + 8, sizeof(lhbuf),
					&lhbuf);
		if (lh == NULL)
			return false;
		data.tid = ntohl(lh->val32);
	} else {
		data.sid = ntohl(lh->val32);
		data.type = XT_L2TP_TYPE_DATA;
	}

	data.version = 3;

	return l2tp_match(info, &data);
}