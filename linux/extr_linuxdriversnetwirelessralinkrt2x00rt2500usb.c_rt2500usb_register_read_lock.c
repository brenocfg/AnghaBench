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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_TIMEOUT ; 
 int /*<<< orphan*/  USB_MULTI_READ ; 
 int /*<<< orphan*/  USB_VENDOR_REQUEST_IN ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_vendor_req_buff_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 rt2500usb_register_read_lock(struct rt2x00_dev *rt2x00dev,
					const unsigned int offset)
{
	__le16 reg;
	rt2x00usb_vendor_req_buff_lock(rt2x00dev, USB_MULTI_READ,
				       USB_VENDOR_REQUEST_IN, offset,
				       &reg, sizeof(reg), REGISTER_TIMEOUT);
	return le16_to_cpu(reg);
}