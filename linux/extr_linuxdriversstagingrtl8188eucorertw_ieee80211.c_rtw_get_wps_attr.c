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
typedef  int uint ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int _VENDOR_SPECIFIC_IE_ ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 

u8 *rtw_get_wps_attr(u8 *wps_ie, uint wps_ielen, u16 target_attr_id, u8 *buf_attr, u32 *len_attr)
{
	u8 *attr_ptr = NULL;
	u8 *target_attr_ptr = NULL;
	u8 wps_oui[4] = {0x00, 0x50, 0xF2, 0x04};

	if (len_attr)
		*len_attr = 0;

	if ((wps_ie[0] != _VENDOR_SPECIFIC_IE_) ||
	    (memcmp(wps_ie + 2, wps_oui, 4)))
		return attr_ptr;

	/*  6 = 1(Element ID) + 1(Length) + 4(WPS OUI) */
	attr_ptr = wps_ie + 6; /* goto first attr */

	while (attr_ptr - wps_ie < wps_ielen) {
		/*  4 = 2(Attribute ID) + 2(Length) */
		u16 attr_id = get_unaligned_be16(attr_ptr);
		u16 attr_data_len = get_unaligned_be16(attr_ptr + 2);
		u16 attr_len = attr_data_len + 4;

		if (attr_id == target_attr_id) {
			target_attr_ptr = attr_ptr;
			if (buf_attr)
				memcpy(buf_attr, attr_ptr, attr_len);
			if (len_attr)
				*len_attr = attr_len;
			break;
		} else {
			attr_ptr += attr_len; /* goto next */
		}
	}
	return target_attr_ptr;
}