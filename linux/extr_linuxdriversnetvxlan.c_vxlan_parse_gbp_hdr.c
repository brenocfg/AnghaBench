#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vxlanhdr_gbp {scalar_t__ policy_applied; scalar_t__ dont_learn; int /*<<< orphan*/  policy_id; } ;
struct vxlanhdr {int vx_flags; } ;
struct vxlan_metadata {int /*<<< orphan*/  gbp; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct TYPE_4__ {int /*<<< orphan*/  tun_flags; } ;
struct TYPE_5__ {int options_len; TYPE_1__ key; } ;
struct TYPE_6__ {TYPE_2__ tun_info; } ;
struct metadata_dst {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNNEL_VXLAN_OPT ; 
 int VXLAN_F_COLLECT_METADATA ; 
 int /*<<< orphan*/  VXLAN_GBP_DONT_LEARN ; 
 int /*<<< orphan*/  VXLAN_GBP_POLICY_APPLIED ; 
 int VXLAN_GBP_USED_BITS ; 
 int VXLAN_HF_GBP ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_dst (struct sk_buff*) ; 

__attribute__((used)) static void vxlan_parse_gbp_hdr(struct vxlanhdr *unparsed,
				struct sk_buff *skb, u32 vxflags,
				struct vxlan_metadata *md)
{
	struct vxlanhdr_gbp *gbp = (struct vxlanhdr_gbp *)unparsed;
	struct metadata_dst *tun_dst;

	if (!(unparsed->vx_flags & VXLAN_HF_GBP))
		goto out;

	md->gbp = ntohs(gbp->policy_id);

	tun_dst = (struct metadata_dst *)skb_dst(skb);
	if (tun_dst) {
		tun_dst->u.tun_info.key.tun_flags |= TUNNEL_VXLAN_OPT;
		tun_dst->u.tun_info.options_len = sizeof(*md);
	}
	if (gbp->dont_learn)
		md->gbp |= VXLAN_GBP_DONT_LEARN;

	if (gbp->policy_applied)
		md->gbp |= VXLAN_GBP_POLICY_APPLIED;

	/* In flow-based mode, GBP is carried in dst_metadata */
	if (!(vxflags & VXLAN_F_COLLECT_METADATA))
		skb->mark = md->gbp;
out:
	unparsed->vx_flags &= ~VXLAN_GBP_USED_BITS;
}