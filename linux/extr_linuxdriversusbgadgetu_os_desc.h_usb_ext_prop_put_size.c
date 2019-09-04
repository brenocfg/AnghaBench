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
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ext_prop_size_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void usb_ext_prop_put_size(u8 *buf, int dw_size)
{
	put_unaligned_le32(dw_size, usb_ext_prop_size_ptr(buf));
}