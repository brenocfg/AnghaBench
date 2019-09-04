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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct usb_function {int dummy; } ;
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; int /*<<< orphan*/  wLength; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ UAC2_CS_CONTROL_SAM_FREQ ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
out_rq_cur(struct usb_function *fn, const struct usb_ctrlrequest *cr)
{
	u16 w_length = le16_to_cpu(cr->wLength);
	u16 w_value = le16_to_cpu(cr->wValue);
	u8 control_selector = w_value >> 8;

	if (control_selector == UAC2_CS_CONTROL_SAM_FREQ)
		return w_length;

	return -EOPNOTSUPP;
}