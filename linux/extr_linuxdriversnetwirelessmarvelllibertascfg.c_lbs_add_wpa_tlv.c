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

/* Variables and functions */

__attribute__((used)) static int lbs_add_wpa_tlv(u8 *tlv, const u8 *ie, u8 ie_len)
{
	size_t tlv_len;

	/*
	 * We need just convert an IE to an TLV. IEs use u8 for the header,
	 *   u8      type
	 *   u8      len
	 *   u8[]    data
	 * but TLVs use __le16 instead:
	 *   __le16  type
	 *   __le16  len
	 *   u8[]    data
	 */
	*tlv++ = *ie++;
	*tlv++ = 0;
	tlv_len = *tlv++ = *ie++;
	*tlv++ = 0;
	while (tlv_len--)
		*tlv++ = *ie++;
	/* the TLV is two bytes larger than the IE */
	return ie_len + 2;
}