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
typedef  int u8 ;
struct tnl_ptk_info {scalar_t__ proto; int hdr_len; void* key; void* seq; int /*<<< orphan*/  flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct gre_base_hdr {int flags; scalar_t__ protocol; } ;
struct erspan_base_hdr {int dummy; } ;
typedef  void* __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_ERSPAN ; 
 int /*<<< orphan*/  ETH_P_ERSPAN2 ; 
 int /*<<< orphan*/  ETH_P_WCCP ; 
 int GRE_CSUM ; 
 int GRE_KEY ; 
 int GRE_ROUTING ; 
 int GRE_SEQ ; 
 int GRE_VERSION ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_session_id (struct erspan_base_hdr*) ; 
 int gre_calc_hlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre_flags_to_tnl_flags (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_compute_pseudo ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_checksum_simple_validate (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_try_convert (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int gre_parse_header(struct sk_buff *skb, struct tnl_ptk_info *tpi,
		     bool *csum_err, __be16 proto, int nhs)
{
	const struct gre_base_hdr *greh;
	__be32 *options;
	int hdr_len;

	if (unlikely(!pskb_may_pull(skb, nhs + sizeof(struct gre_base_hdr))))
		return -EINVAL;

	greh = (struct gre_base_hdr *)(skb->data + nhs);
	if (unlikely(greh->flags & (GRE_VERSION | GRE_ROUTING)))
		return -EINVAL;

	tpi->flags = gre_flags_to_tnl_flags(greh->flags);
	hdr_len = gre_calc_hlen(tpi->flags);

	if (!pskb_may_pull(skb, nhs + hdr_len))
		return -EINVAL;

	greh = (struct gre_base_hdr *)(skb->data + nhs);
	tpi->proto = greh->protocol;

	options = (__be32 *)(greh + 1);
	if (greh->flags & GRE_CSUM) {
		if (!skb_checksum_simple_validate(skb)) {
			skb_checksum_try_convert(skb, IPPROTO_GRE,
						 null_compute_pseudo);
		} else if (csum_err) {
			*csum_err = true;
			return -EINVAL;
		}

		options++;
	}

	if (greh->flags & GRE_KEY) {
		tpi->key = *options;
		options++;
	} else {
		tpi->key = 0;
	}
	if (unlikely(greh->flags & GRE_SEQ)) {
		tpi->seq = *options;
		options++;
	} else {
		tpi->seq = 0;
	}
	/* WCCP version 1 and 2 protocol decoding.
	 * - Change protocol to IPv4/IPv6
	 * - When dealing with WCCPv2, Skip extra 4 bytes in GRE header
	 */
	if (greh->flags == 0 && tpi->proto == htons(ETH_P_WCCP)) {
		tpi->proto = proto;
		if ((*(u8 *)options & 0xF0) != 0x40)
			hdr_len += 4;
	}
	tpi->hdr_len = hdr_len;

	/* ERSPAN ver 1 and 2 protocol sets GRE key field
	 * to 0 and sets the configured key in the
	 * inner erspan header field
	 */
	if (greh->protocol == htons(ETH_P_ERSPAN) ||
	    greh->protocol == htons(ETH_P_ERSPAN2)) {
		struct erspan_base_hdr *ershdr;

		if (!pskb_may_pull(skb, nhs + hdr_len + sizeof(*ershdr)))
			return -EINVAL;

		ershdr = (struct erspan_base_hdr *)options;
		tpi->key = cpu_to_be32(get_session_id(ershdr));
	}

	return hdr_len;
}