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
struct usbctlx_rmem_completor {unsigned int len; struct usbctlx_completor head; void* data; struct hfa384x_usb_rmemresp* rmemresp; } ;
struct hfa384x_usb_rmemresp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbctlx_rmem_completor_fn ; 

__attribute__((used)) static inline struct usbctlx_completor *
init_rmem_completor(struct usbctlx_rmem_completor *completor,
		    struct hfa384x_usb_rmemresp *rmemresp,
		    void *data,
		    unsigned int len)
{
	completor->head.complete = usbctlx_rmem_completor_fn;
	completor->rmemresp = rmemresp;
	completor->data = data;
	completor->len = len;
	return &completor->head;
}