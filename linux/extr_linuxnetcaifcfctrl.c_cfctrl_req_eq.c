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
struct cfctrl_request_info {scalar_t__ cmd; scalar_t__ channel_id; int /*<<< orphan*/  param; } ;

/* Variables and functions */
 scalar_t__ CFCTRL_CMD_LINK_SETUP ; 
 int param_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cfctrl_req_eq(const struct cfctrl_request_info *r1,
			  const struct cfctrl_request_info *r2)
{
	if (r1->cmd != r2->cmd)
		return false;
	if (r1->cmd == CFCTRL_CMD_LINK_SETUP)
		return param_eq(&r1->param, &r2->param);
	else
		return r1->channel_id == r2->channel_id;
}