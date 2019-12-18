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
union l2tp_val {int /*<<< orphan*/ * val16; int /*<<< orphan*/  val32; } ;
typedef  int u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct xt_l2tp_info {int dummy; } ;
struct xt_action_param {scalar_t__ fragoff; struct xt_l2tp_info* matchinfo; } ;
struct udphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct l2tp_data {scalar_t__ type; int version; void* sid; void* tid; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int L2TP_HDR_L_BIT ; 
 int L2TP_HDR_T_BIT ; 
 int L2TP_HDR_VER ; 
 scalar_t__ XT_L2TP_TYPE_CONTROL ; 
 scalar_t__ XT_L2TP_TYPE_DATA ; 
 int l2tp_match (struct xt_l2tp_info const*,struct l2tp_data*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 union l2tp_val* skb_header_pointer (struct sk_buff const*,int,int,union l2tp_val*) ; 

__attribute__((used)) static bool l2tp_udp_mt(const struct sk_buff *skb, struct xt_action_param *par, u16 thoff)
{
	const struct xt_l2tp_info *info = par->matchinfo;
	int uhlen = sizeof(struct udphdr);
	int offs = thoff + uhlen;
	union l2tp_val *lh;
	union l2tp_val lhbuf;
	u16 flags;
	struct l2tp_data data = { 0, };

	if (par->fragoff != 0)
		return false;

	/* Extract L2TP header fields. The flags in the first 16 bits
	 * tell us where the other fields are.
	 */
	lh = skb_header_pointer(skb, offs, 2, &lhbuf);
	if (lh == NULL)
		return false;

	flags = ntohs(lh->val16[0]);
	if (flags & L2TP_HDR_T_BIT)
		data.type = XT_L2TP_TYPE_CONTROL;
	else
		data.type = XT_L2TP_TYPE_DATA;
	data.version = (u8) flags & L2TP_HDR_VER;

	/* Now extract the L2TP tid/sid. These are in different places
	 * for L2TPv2 (rfc2661) and L2TPv3 (rfc3931). For L2TPv2, we
	 * must also check to see if the length field is present,
	 * since this affects the offsets into the packet of the
	 * tid/sid fields.
	 */
	if (data.version == 3) {
		lh = skb_header_pointer(skb, offs + 4, 4, &lhbuf);
		if (lh == NULL)
			return false;
		if (data.type == XT_L2TP_TYPE_CONTROL)
			data.tid = ntohl(lh->val32);
		else
			data.sid = ntohl(lh->val32);
	} else if (data.version == 2) {
		if (flags & L2TP_HDR_L_BIT)
			offs += 2;
		lh = skb_header_pointer(skb, offs + 2, 4, &lhbuf);
		if (lh == NULL)
			return false;
		data.tid = (u32) ntohs(lh->val16[0]);
		data.sid = (u32) ntohs(lh->val16[1]);
	} else
		return false;

	return l2tp_match(info, &data);
}