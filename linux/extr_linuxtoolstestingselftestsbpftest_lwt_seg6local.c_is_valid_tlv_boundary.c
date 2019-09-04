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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tlv ;
struct sr6_tlv_t {scalar_t__ type; int len; } ;
struct ip6_srh_t {int first_segment; int hdrlen; } ;
struct ip6_addr_t {int dummy; } ;
struct __sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SR6_TLV_HMAC ; 
 scalar_t__ SR6_TLV_PADDING ; 
 int bpf_skb_load_bytes (struct __sk_buff*,int,struct sr6_tlv_t*,int) ; 

__attribute__((always_inline))
int is_valid_tlv_boundary(struct __sk_buff *skb, struct ip6_srh_t *srh,
			  uint32_t *tlv_off, uint32_t *pad_size,
			  uint32_t *pad_off)
{
	uint32_t srh_off, cur_off;
	int offset_valid = 0;
	int err;

	srh_off = (char *)srh - (char *)(long)skb->data;
	// cur_off = end of segments, start of possible TLVs
	cur_off = srh_off + sizeof(*srh) +
		sizeof(struct ip6_addr_t) * (srh->first_segment + 1);

	*pad_off = 0;

	// we can only go as far as ~10 TLVs due to the BPF max stack size
	#pragma clang loop unroll(full)
	for (int i = 0; i < 10; i++) {
		struct sr6_tlv_t tlv;

		if (cur_off == *tlv_off)
			offset_valid = 1;

		if (cur_off >= srh_off + ((srh->hdrlen + 1) << 3))
			break;

		err = bpf_skb_load_bytes(skb, cur_off, &tlv, sizeof(tlv));
		if (err)
			return err;

		if (tlv.type == SR6_TLV_PADDING) {
			*pad_size = tlv.len + sizeof(tlv);
			*pad_off = cur_off;

			if (*tlv_off == srh_off) {
				*tlv_off = cur_off;
				offset_valid = 1;
			}
			break;

		} else if (tlv.type == SR6_TLV_HMAC) {
			break;
		}

		cur_off += sizeof(tlv) + tlv.len;
	} // we reached the padding or HMAC TLVs, or the end of the SRH

	if (*pad_off == 0)
		*pad_off = cur_off;

	if (*tlv_off == -1)
		*tlv_off = cur_off;
	else if (!offset_valid)
		return -EINVAL;

	return 0;
}