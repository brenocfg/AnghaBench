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
struct hfa384x_usb_rridresp {int /*<<< orphan*/  frmlen; int /*<<< orphan*/  data; int /*<<< orphan*/  rid; } ;
struct hfa384x_rridresult {int rid; int riddata_len; int /*<<< orphan*/  riddata; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbctlx_get_rridresult(const struct hfa384x_usb_rridresp *rridresp,
		       struct hfa384x_rridresult *result)
{
	result->rid = le16_to_cpu(rridresp->rid);
	result->riddata = rridresp->data;
	result->riddata_len = ((le16_to_cpu(rridresp->frmlen) - 1) * 2);
}