#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct registry_priv {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_4__ {struct mlme_priv mlmepriv; struct registry_priv registrypriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int rtw_set_chplan_cmd (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int rtw_set_channel_plan(_adapter *adapter, u8 channel_plan)
{
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;

	//handle by cmd_thread to sync with scan operation
	return rtw_set_chplan_cmd(adapter, channel_plan, 1);
}