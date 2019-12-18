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
struct pm_qos_request {scalar_t__ pm_qos_class; } ;

/* Variables and functions */

int pm_qos_request_active(struct pm_qos_request *req)
{
	return req->pm_qos_class != 0;
}