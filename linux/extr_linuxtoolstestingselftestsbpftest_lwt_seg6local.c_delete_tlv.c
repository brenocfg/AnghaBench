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
typedef  int /*<<< orphan*/  tlv ;
struct sr6_tlv_t {int len; } ;
struct ip6_srh_t {int dummy; } ;
struct __sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int bpf_lwt_seg6_adjust_srh (struct __sk_buff*,int,int) ; 
 int bpf_skb_load_bytes (struct __sk_buff*,int,struct sr6_tlv_t*,int) ; 
 int is_valid_tlv_boundary (struct __sk_buff*,struct ip6_srh_t*,int*,int*,int*) ; 
 int update_tlv_pad (struct __sk_buff*,int,int,int) ; 

__attribute__((always_inline))
int delete_tlv(struct __sk_buff *skb, struct ip6_srh_t *srh,
	       uint32_t tlv_off)
{
	uint32_t srh_off = (char *)srh - (char *)(long)skb->data;
	uint8_t len_remaining, new_pad;
	uint32_t partial_srh_len;
	uint32_t pad_off = 0;
	uint32_t pad_size = 0;
	struct sr6_tlv_t tlv;
	int err;

	tlv_off += srh_off;

	err = is_valid_tlv_boundary(skb, srh, &tlv_off, &pad_size, &pad_off);
	if (err)
		return err;

	err = bpf_skb_load_bytes(skb, tlv_off, &tlv, sizeof(tlv));
	if (err)
		return err;

	err = bpf_lwt_seg6_adjust_srh(skb, tlv_off, -(sizeof(tlv) + tlv.len));
	if (err)
		return err;

	pad_off -= sizeof(tlv) + tlv.len;
	partial_srh_len = pad_off - srh_off;
	len_remaining = partial_srh_len % 8;
	new_pad = 8 - len_remaining;
	if (new_pad == 1) // cannot pad for 1 byte only
		new_pad = 9;
	else if (new_pad == 8)
		new_pad = 0;

	return update_tlv_pad(skb, new_pad, pad_size, pad_off);
}