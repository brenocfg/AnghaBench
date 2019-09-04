#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cmd_obj {struct cmd_obj* parmbuf; } ;
struct TYPE_3__ {int bcompleted; } ;
struct TYPE_4__ {TYPE_1__ workparam; } ;
struct _adapter {TYPE_2__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 

void r8712_getbbrfreg_cmdrsp_callback(struct _adapter *padapter,
				      struct cmd_obj *pcmd)
{
	kfree(pcmd->parmbuf);
	kfree(pcmd);
	padapter->mppriv.workparam.bcompleted = true;
}