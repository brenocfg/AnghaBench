#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlme_priv {int dummy; } ;
struct mlme_ext_priv {int /*<<< orphan*/  channel_list; int /*<<< orphan*/  max_chan_nums; int /*<<< orphan*/  channel_set; } ;
struct SetChannelPlan_param {int /*<<< orphan*/  channel_plan; } ;
struct TYPE_5__ {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  init_channel_list (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_channel_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 set_chplan_hdl(_adapter *padapter, unsigned char *pbuf)
{
	struct SetChannelPlan_param *setChannelPlan_param;
	struct mlme_priv		*pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;

	if(!pbuf)
		return H2C_PARAMETERS_ERROR;

	setChannelPlan_param = (struct SetChannelPlan_param *)pbuf;

	pmlmeext->max_chan_nums = init_channel_set(padapter, setChannelPlan_param->channel_plan, pmlmeext->channel_set);
	init_channel_list(padapter, pmlmeext->channel_set, pmlmeext->max_chan_nums, &pmlmeext->channel_list);	

	return 	H2C_SUCCESS;
}