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
struct sr6_tlv {int len; } ;
struct ipv6_sr_hdr {scalar_t__ type; int hdrlen; int segments_left; int first_segment; } ;

/* Variables and functions */
 scalar_t__ IPV6_SRCRT_TYPE_4 ; 

bool seg6_validate_srh(struct ipv6_sr_hdr *srh, int len)
{
	int trailing;
	unsigned int tlv_offset;

	if (srh->type != IPV6_SRCRT_TYPE_4)
		return false;

	if (((srh->hdrlen + 1) << 3) != len)
		return false;

	if (srh->segments_left > srh->first_segment)
		return false;

	tlv_offset = sizeof(*srh) + ((srh->first_segment + 1) << 4);

	trailing = len - tlv_offset;
	if (trailing < 0)
		return false;

	while (trailing) {
		struct sr6_tlv *tlv;
		unsigned int tlv_len;

		if (trailing < sizeof(*tlv))
			return false;

		tlv = (struct sr6_tlv *)((unsigned char *)srh + tlv_offset);
		tlv_len = sizeof(*tlv) + tlv->len;

		trailing -= tlv_len;
		if (trailing < 0)
			return false;

		tlv_offset += tlv_len;
	}

	return true;
}