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
struct usbctlx_completor {int /*<<< orphan*/  complete; } ;
struct usbctlx_cmd_completor {struct usbctlx_completor head; struct hfa384x_cmdresult* result; struct hfa384x_usb_statusresp const* cmdresp; } ;
struct hfa384x_usb_statusresp {int dummy; } ;
struct hfa384x_cmdresult {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbctlx_cmd_completor_fn ; 

__attribute__((used)) static inline struct usbctlx_completor *
init_cmd_completor(struct usbctlx_cmd_completor *completor,
		   const struct hfa384x_usb_statusresp *cmdresp,
		   struct hfa384x_cmdresult *result)
{
	completor->head.complete = usbctlx_cmd_completor_fn;
	completor->cmdresp = cmdresp;
	completor->result = result;
	return &completor->head;
}