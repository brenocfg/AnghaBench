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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int USB_EXT_PROP_B_PROPERTY_NAME ; 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * usb_ext_prop_name_len_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_ext_prop_name_ptr (int /*<<< orphan*/ *) ; 
 int utf8s_to_utf16s (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int usb_ext_prop_put_name(u8 *buf, const char *name, int pnl)
{
	int result;

	put_unaligned_le16(pnl, usb_ext_prop_name_len_ptr(buf));
	result = utf8s_to_utf16s(name, strlen(name), UTF16_LITTLE_ENDIAN,
		(wchar_t *) usb_ext_prop_name_ptr(buf), pnl - 2);
	if (result < 0)
		return result;

	put_unaligned_le16(0, &buf[USB_EXT_PROP_B_PROPERTY_NAME + pnl - 2]);

	return pnl;
}