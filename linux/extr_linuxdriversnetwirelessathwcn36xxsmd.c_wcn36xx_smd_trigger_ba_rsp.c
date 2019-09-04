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
struct wcn36xx_hal_trigger_ba_rsp_msg {int status; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int wcn36xx_smd_trigger_ba_rsp(void *buf, int len)
{
	struct wcn36xx_hal_trigger_ba_rsp_msg *rsp;

	if (len < sizeof(*rsp))
		return -EINVAL;

	rsp = (struct wcn36xx_hal_trigger_ba_rsp_msg *) buf;
	return rsp->status;
}