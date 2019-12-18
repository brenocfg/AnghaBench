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
struct sk_buff {int dummy; } ;
struct mpls_shim_hdr {int dummy; } ;
struct mpls_route {int dummy; } ;
struct mpls_entry_decoded {scalar_t__ label; int /*<<< orphan*/  bos; } ;
struct ipv6hdr {scalar_t__ nexthdr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct iphdr {int version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int MAX_MP_SELECT_LABELS ; 
 scalar_t__ MPLS_LABEL_ENTROPY ; 
 scalar_t__ MPLS_LABEL_FIRST_UNRESERVED ; 
 int /*<<< orphan*/  __ipv6_addr_jhash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_1word (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_3words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct mpls_entry_decoded mpls_entry_decode (struct mpls_shim_hdr*) ; 
 struct mpls_shim_hdr* mpls_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static u32 mpls_multipath_hash(struct mpls_route *rt, struct sk_buff *skb)
{
	struct mpls_entry_decoded dec;
	unsigned int mpls_hdr_len = 0;
	struct mpls_shim_hdr *hdr;
	bool eli_seen = false;
	int label_index;
	u32 hash = 0;

	for (label_index = 0; label_index < MAX_MP_SELECT_LABELS;
	     label_index++) {
		mpls_hdr_len += sizeof(*hdr);
		if (!pskb_may_pull(skb, mpls_hdr_len))
			break;

		/* Read and decode the current label */
		hdr = mpls_hdr(skb) + label_index;
		dec = mpls_entry_decode(hdr);

		/* RFC6790 - reserved labels MUST NOT be used as keys
		 * for the load-balancing function
		 */
		if (likely(dec.label >= MPLS_LABEL_FIRST_UNRESERVED)) {
			hash = jhash_1word(dec.label, hash);

			/* The entropy label follows the entropy label
			 * indicator, so this means that the entropy
			 * label was just added to the hash - no need to
			 * go any deeper either in the label stack or in the
			 * payload
			 */
			if (eli_seen)
				break;
		} else if (dec.label == MPLS_LABEL_ENTROPY) {
			eli_seen = true;
		}

		if (!dec.bos)
			continue;

		/* found bottom label; does skb have room for a header? */
		if (pskb_may_pull(skb, mpls_hdr_len + sizeof(struct iphdr))) {
			const struct iphdr *v4hdr;

			v4hdr = (const struct iphdr *)(hdr + 1);
			if (v4hdr->version == 4) {
				hash = jhash_3words(ntohl(v4hdr->saddr),
						    ntohl(v4hdr->daddr),
						    v4hdr->protocol, hash);
			} else if (v4hdr->version == 6 &&
				   pskb_may_pull(skb, mpls_hdr_len +
						 sizeof(struct ipv6hdr))) {
				const struct ipv6hdr *v6hdr;

				v6hdr = (const struct ipv6hdr *)(hdr + 1);
				hash = __ipv6_addr_jhash(&v6hdr->saddr, hash);
				hash = __ipv6_addr_jhash(&v6hdr->daddr, hash);
				hash = jhash_1word(v6hdr->nexthdr, hash);
			}
		}

		break;
	}

	return hash;
}