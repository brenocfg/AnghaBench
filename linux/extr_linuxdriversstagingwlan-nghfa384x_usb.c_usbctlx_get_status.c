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
struct hfa384x_usb_statusresp {int /*<<< orphan*/  resp2; int /*<<< orphan*/  resp1; int /*<<< orphan*/  resp0; int /*<<< orphan*/  status; } ;
struct hfa384x_cmdresult {int status; void* resp2; void* resp1; void* resp0; } ;

/* Variables and functions */
 int HFA384x_STATUS_RESULT ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,void*,void*,void*) ; 

__attribute__((used)) static int
usbctlx_get_status(const struct hfa384x_usb_statusresp *cmdresp,
		   struct hfa384x_cmdresult *result)
{
	result->status = le16_to_cpu(cmdresp->status);
	result->resp0 = le16_to_cpu(cmdresp->resp0);
	result->resp1 = le16_to_cpu(cmdresp->resp1);
	result->resp2 = le16_to_cpu(cmdresp->resp2);

	pr_debug("cmdresult:status=0x%04x resp0=0x%04x resp1=0x%04x resp2=0x%04x\n",
		 result->status, result->resp0, result->resp1, result->resp2);

	return result->status & HFA384x_STATUS_RESULT;
}