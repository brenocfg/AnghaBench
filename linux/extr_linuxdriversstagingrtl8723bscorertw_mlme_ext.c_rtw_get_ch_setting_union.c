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
typedef  scalar_t__ u8 ;
struct mlme_ext_priv {scalar_t__ cur_ch_offset; scalar_t__ cur_bwmode; scalar_t__ cur_channel; } ;
struct dvobj_priv {struct adapter* padapters; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_WIDTH_20 ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int _FW_LINKED ; 
 int _FW_UNDER_LINKING ; 
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 
 int /*<<< orphan*/  check_fwstate (int /*<<< orphan*/ *,int) ; 

int rtw_get_ch_setting_union(struct adapter *adapter, u8 *ch, u8 *bw, u8 *offset)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct adapter *iface;
	struct mlme_ext_priv *mlmeext;
	u8 ch_ret = 0;
	u8 bw_ret = CHANNEL_WIDTH_20;
	u8 offset_ret = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	if (ch)
		*ch = 0;
	if (bw)
		*bw = CHANNEL_WIDTH_20;
	if (offset)
		*offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	iface = dvobj->padapters;
	mlmeext = &iface->mlmeextpriv;

	if (!check_fwstate(&iface->mlmepriv, _FW_LINKED|_FW_UNDER_LINKING))
		return 0;

	ch_ret = mlmeext->cur_channel;
	bw_ret = mlmeext->cur_bwmode;
	offset_ret = mlmeext->cur_ch_offset;

	return 1;
}