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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ext_prop_data_len_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_ext_prop_data_ptr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void usb_ext_prop_put_binary(u8 *buf, int pnl, const u8 *data,
					   int data_len)
{
	put_unaligned_le32(data_len, usb_ext_prop_data_len_ptr(buf, pnl));
	memcpy(usb_ext_prop_data_ptr(buf, pnl), data, data_len);
}