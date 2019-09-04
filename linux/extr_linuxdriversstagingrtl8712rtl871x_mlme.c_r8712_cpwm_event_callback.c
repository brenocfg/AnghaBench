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
typedef  int /*<<< orphan*/  u8 ;
struct reportpwrstate_parm {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__ cpwm_tog; } ;
struct _adapter {TYPE_1__ pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_cpwm_int_hdl (struct _adapter*,struct reportpwrstate_parm*) ; 

void r8712_cpwm_event_callback(struct _adapter *adapter, u8 *pbuf)
{
	struct reportpwrstate_parm *preportpwrstate =
			 (struct reportpwrstate_parm *)pbuf;

	preportpwrstate->state |= (u8)(adapter->pwrctrlpriv.cpwm_tog + 0x80);
	r8712_cpwm_int_hdl(adapter, preportpwrstate);
}