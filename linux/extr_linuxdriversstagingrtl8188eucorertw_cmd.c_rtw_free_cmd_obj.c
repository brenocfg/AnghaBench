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
struct cmd_obj {scalar_t__ cmdcode; scalar_t__ rspsz; struct cmd_obj* rsp; struct cmd_obj* parmbuf; } ;

/* Variables and functions */
 scalar_t__ _CreateBss_CMD_ ; 
 scalar_t__ _JoinBss_CMD_ ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 

void rtw_free_cmd_obj(struct cmd_obj *pcmd)
{
	if ((pcmd->cmdcode != _JoinBss_CMD_) && (pcmd->cmdcode != _CreateBss_CMD_)) {
		/* free parmbuf in cmd_obj */
		kfree(pcmd->parmbuf);
	}

	if (pcmd->rsp) {
		if (pcmd->rspsz != 0) {
			/* free rsp in cmd_obj */
			kfree(pcmd->rsp);
		}
	}

	/* free cmd_obj */
	kfree(pcmd);
}