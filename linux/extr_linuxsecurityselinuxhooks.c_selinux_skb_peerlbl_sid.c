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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int security_net_peersid_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int selinux_netlbl_skbuff_getsid (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int selinux_xfrm_skb_sid (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int selinux_skb_peerlbl_sid(struct sk_buff *skb, u16 family, u32 *sid)
{
	int err;
	u32 xfrm_sid;
	u32 nlbl_sid;
	u32 nlbl_type;

	err = selinux_xfrm_skb_sid(skb, &xfrm_sid);
	if (unlikely(err))
		return -EACCES;
	err = selinux_netlbl_skbuff_getsid(skb, family, &nlbl_type, &nlbl_sid);
	if (unlikely(err))
		return -EACCES;

	err = security_net_peersid_resolve(&selinux_state, nlbl_sid,
					   nlbl_type, xfrm_sid, sid);
	if (unlikely(err)) {
		pr_warn(
		       "SELinux: failure in selinux_skb_peerlbl_sid(),"
		       " unable to determine packet's peer label\n");
		return -EACCES;
	}

	return 0;
}