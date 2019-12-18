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
struct xt_action_param {struct ip6t_srh* matchinfo; } ;
struct sk_buff {int len; } ;
struct ipv6_sr_hdr {scalar_t__ type; scalar_t__ segments_left; scalar_t__ first_segment; scalar_t__ nexthdr; scalar_t__ hdrlen; scalar_t__ tag; } ;
struct ip6t_srh {int mt_flags; scalar_t__ next_hdr; scalar_t__ hdr_len; scalar_t__ segs_left; scalar_t__ last_entry; scalar_t__ tag; } ;
typedef  int /*<<< orphan*/  _srh ;

/* Variables and functions */
 int /*<<< orphan*/  IP6T_SRH_INV_LAST_EQ ; 
 int /*<<< orphan*/  IP6T_SRH_INV_LAST_GT ; 
 int /*<<< orphan*/  IP6T_SRH_INV_LAST_LT ; 
 int /*<<< orphan*/  IP6T_SRH_INV_LEN_EQ ; 
 int /*<<< orphan*/  IP6T_SRH_INV_LEN_GT ; 
 int /*<<< orphan*/  IP6T_SRH_INV_LEN_LT ; 
 int /*<<< orphan*/  IP6T_SRH_INV_NEXTHDR ; 
 int /*<<< orphan*/  IP6T_SRH_INV_SEGS_EQ ; 
 int /*<<< orphan*/  IP6T_SRH_INV_SEGS_GT ; 
 int /*<<< orphan*/  IP6T_SRH_INV_SEGS_LT ; 
 int /*<<< orphan*/  IP6T_SRH_INV_TAG ; 
 int IP6T_SRH_LAST_EQ ; 
 int IP6T_SRH_LAST_GT ; 
 int IP6T_SRH_LAST_LT ; 
 int IP6T_SRH_LEN_EQ ; 
 int IP6T_SRH_LEN_GT ; 
 int IP6T_SRH_LEN_LT ; 
 int IP6T_SRH_NEXTHDR ; 
 int IP6T_SRH_SEGS_EQ ; 
 int IP6T_SRH_SEGS_GT ; 
 int IP6T_SRH_SEGS_LT ; 
 int IP6T_SRH_TAG ; 
 int /*<<< orphan*/  IPPROTO_ROUTING ; 
 scalar_t__ IPV6_SRCRT_TYPE_4 ; 
 scalar_t__ NF_SRH_INVF (struct ip6t_srh const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ipv6_find_hdr (struct sk_buff const*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_optlen (struct ipv6_sr_hdr*) ; 
 struct ipv6_sr_hdr* skb_header_pointer (struct sk_buff const*,int,int,struct ipv6_sr_hdr*) ; 

__attribute__((used)) static bool srh_mt6(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ip6t_srh *srhinfo = par->matchinfo;
	struct ipv6_sr_hdr *srh;
	struct ipv6_sr_hdr _srh;
	int hdrlen, srhoff = 0;

	if (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, NULL, NULL) < 0)
		return false;
	srh = skb_header_pointer(skb, srhoff, sizeof(_srh), &_srh);
	if (!srh)
		return false;

	hdrlen = ipv6_optlen(srh);
	if (skb->len - srhoff < hdrlen)
		return false;

	if (srh->type != IPV6_SRCRT_TYPE_4)
		return false;

	if (srh->segments_left > srh->first_segment)
		return false;

	/* Next Header matching */
	if (srhinfo->mt_flags & IP6T_SRH_NEXTHDR)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_NEXTHDR,
				!(srh->nexthdr == srhinfo->next_hdr)))
			return false;

	/* Header Extension Length matching */
	if (srhinfo->mt_flags & IP6T_SRH_LEN_EQ)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_EQ,
				!(srh->hdrlen == srhinfo->hdr_len)))
			return false;

	if (srhinfo->mt_flags & IP6T_SRH_LEN_GT)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_GT,
				!(srh->hdrlen > srhinfo->hdr_len)))
			return false;

	if (srhinfo->mt_flags & IP6T_SRH_LEN_LT)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LEN_LT,
				!(srh->hdrlen < srhinfo->hdr_len)))
			return false;

	/* Segments Left matching */
	if (srhinfo->mt_flags & IP6T_SRH_SEGS_EQ)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_EQ,
				!(srh->segments_left == srhinfo->segs_left)))
			return false;

	if (srhinfo->mt_flags & IP6T_SRH_SEGS_GT)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_GT,
				!(srh->segments_left > srhinfo->segs_left)))
			return false;

	if (srhinfo->mt_flags & IP6T_SRH_SEGS_LT)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_SEGS_LT,
				!(srh->segments_left < srhinfo->segs_left)))
			return false;

	/**
	 * Last Entry matching
	 * Last_Entry field was introduced in revision 6 of the SRH draft.
	 * It was called First_Segment in the previous revision
	 */
	if (srhinfo->mt_flags & IP6T_SRH_LAST_EQ)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_EQ,
				!(srh->first_segment == srhinfo->last_entry)))
			return false;

	if (srhinfo->mt_flags & IP6T_SRH_LAST_GT)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_GT,
				!(srh->first_segment > srhinfo->last_entry)))
			return false;

	if (srhinfo->mt_flags & IP6T_SRH_LAST_LT)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_LAST_LT,
				!(srh->first_segment < srhinfo->last_entry)))
			return false;

	/**
	 * Tag matchig
	 * Tag field was introduced in revision 6 of the SRH draft.
	 */
	if (srhinfo->mt_flags & IP6T_SRH_TAG)
		if (NF_SRH_INVF(srhinfo, IP6T_SRH_INV_TAG,
				!(srh->tag == srhinfo->tag)))
			return false;
	return true;
}