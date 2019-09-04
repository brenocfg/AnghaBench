#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ actual; scalar_t__ length; } ;
struct dwc3_request {TYPE_1__ request; } ;

/* Variables and functions */

__attribute__((used)) static bool dwc3_gadget_ep_request_completed(struct dwc3_request *req)
{
	return req->request.actual == req->request.length;
}