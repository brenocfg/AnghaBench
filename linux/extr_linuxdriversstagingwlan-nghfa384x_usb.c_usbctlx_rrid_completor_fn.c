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
struct usbctlx_rrid_completor {scalar_t__ riddatalen; int /*<<< orphan*/  riddata; int /*<<< orphan*/  rridresp; } ;
struct usbctlx_completor {int dummy; } ;
struct hfa384x_rridresult {scalar_t__ riddata_len; int /*<<< orphan*/  riddata; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usbctlx_get_rridresult (int /*<<< orphan*/ ,struct hfa384x_rridresult*) ; 

__attribute__((used)) static int usbctlx_rrid_completor_fn(struct usbctlx_completor *head)
{
	struct usbctlx_rrid_completor *complete;
	struct hfa384x_rridresult rridresult;

	complete = (struct usbctlx_rrid_completor *)head;
	usbctlx_get_rridresult(complete->rridresp, &rridresult);

	/* Validate the length, note body len calculation in bytes */
	if (rridresult.riddata_len != complete->riddatalen) {
		pr_warn("RID len mismatch, rid=0x%04x hlen=%d fwlen=%d\n",
			rridresult.rid,
			complete->riddatalen, rridresult.riddata_len);
		return -ENODATA;
	}

	memcpy(complete->riddata, rridresult.riddata, complete->riddatalen);
	return 0;
}