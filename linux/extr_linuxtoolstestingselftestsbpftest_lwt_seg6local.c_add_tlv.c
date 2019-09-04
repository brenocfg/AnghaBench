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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct sr6_tlv_t {scalar_t__ type; int len; } ;
struct ip6_srh_t {int dummy; } ;
struct __sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SR6_TLV_HMAC ; 
 scalar_t__ SR6_TLV_PADDING ; 
 int bpf_lwt_seg6_adjust_srh (struct __sk_buff*,int,int) ; 
 int bpf_lwt_seg6_store_bytes (struct __sk_buff*,int,void*,int) ; 
 int is_valid_tlv_boundary (struct __sk_buff*,struct ip6_srh_t*,int*,int*,int*) ; 
 int update_tlv_pad (struct __sk_buff*,int,int,int) ; 

__attribute__((always_inline))
int add_tlv(struct __sk_buff *skb, struct ip6_srh_t *srh, uint32_t tlv_off,
	    struct sr6_tlv_t *itlv, uint8_t tlv_size)
{
	uint32_t srh_off = (char *)srh - (char *)(long)skb->data;
	uint8_t len_remaining, new_pad;
	uint32_t pad_off = 0;
	uint32_t pad_size = 0;
	uint32_t partial_srh_len;
	int err;

	if (tlv_off != -1)
		tlv_off += srh_off;

	if (itlv->type == SR6_TLV_PADDING || itlv->type == SR6_TLV_HMAC)
		return -EINVAL;

	err = is_valid_tlv_boundary(skb, srh, &tlv_off, &pad_size, &pad_off);
	if (err)
		return err;

	err = bpf_lwt_seg6_adjust_srh(skb, tlv_off, sizeof(*itlv) + itlv->len);
	if (err)
		return err;

	err = bpf_lwt_seg6_store_bytes(skb, tlv_off, (void *)itlv, tlv_size);
	if (err)
		return err;

	// the following can't be moved inside update_tlv_pad because the
	// bpf verifier has some issues with it
	pad_off += sizeof(*itlv) + itlv->len;
	partial_srh_len = pad_off - srh_off;
	len_remaining = partial_srh_len % 8;
	new_pad = 8 - len_remaining;

	if (new_pad == 1) // cannot pad for 1 byte only
		new_pad = 9;
	else if (new_pad == 8)
		new_pad = 0;

	return update_tlv_pad(skb, new_pad, pad_size, pad_off);
}