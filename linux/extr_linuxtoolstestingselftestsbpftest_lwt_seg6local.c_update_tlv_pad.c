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
typedef  scalar_t__ uint32_t ;
struct sr6_tlv_t {scalar_t__ len; int /*<<< orphan*/  type; } ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR6_TLV_PADDING ; 
 int bpf_lwt_seg6_adjust_srh (struct __sk_buff*,scalar_t__,int) ; 
 int bpf_lwt_seg6_store_bytes (struct __sk_buff*,scalar_t__,void*,scalar_t__) ; 

__attribute__((always_inline))
int update_tlv_pad(struct __sk_buff *skb, uint32_t new_pad,
		   uint32_t old_pad, uint32_t pad_off)
{
	int err;

	if (new_pad != old_pad) {
		err = bpf_lwt_seg6_adjust_srh(skb, pad_off,
					  (int) new_pad - (int) old_pad);
		if (err)
			return err;
	}

	if (new_pad > 0) {
		char pad_tlv_buf[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0};
		struct sr6_tlv_t *pad_tlv = (struct sr6_tlv_t *) pad_tlv_buf;

		pad_tlv->type = SR6_TLV_PADDING;
		pad_tlv->len = new_pad - 2;

		err = bpf_lwt_seg6_store_bytes(skb, pad_off,
					       (void *)pad_tlv_buf, new_pad);
		if (err)
			return err;
	}

	return 0;
}