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
struct r8192_priv {scalar_t__ ResetProgress; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int COMP_INIT ; 
 int COMP_POWER ; 
 int COMP_RF ; 
 char* DRV_NAME ; 
 scalar_t__ RESET_TYPE_SILENT ; 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (int,char*) ; 
 int /*<<< orphan*/  UMH_WAIT_PROC ; 
 int /*<<< orphan*/  call_usermodehelper (char const*,char**,char**,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_check_ac_dc_power(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	static char const ac_dc_script[] = "/etc/acpi/wireless-rtl-ac-dc-power.sh";
	char *argv[] = {(char *)ac_dc_script, DRV_NAME, NULL};
	static char *envp[] = {"HOME=/",
			"TERM=linux",
			"PATH=/usr/bin:/bin",
			 NULL};

	if (priv->ResetProgress == RESET_TYPE_SILENT) {
		RT_TRACE((COMP_INIT | COMP_POWER | COMP_RF),
			 "GPIOChangeRFWorkItemCallBack(): Silent Reset!!!!!!!\n");
		return;
	}

	if (priv->rtllib->state != RTLLIB_LINKED)
		return;
	call_usermodehelper(ac_dc_script, argv, envp, UMH_WAIT_PROC);

	return;
}