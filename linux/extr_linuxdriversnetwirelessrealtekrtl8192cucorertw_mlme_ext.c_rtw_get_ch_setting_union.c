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
typedef  scalar_t__ u8 ;
struct mlme_ext_priv {scalar_t__ cur_channel; scalar_t__ cur_bwmode; scalar_t__ cur_ch_offset; } ;
struct dvobj_priv {int iface_nums; TYPE_1__** padapters; } ;
struct TYPE_4__ {int /*<<< orphan*/  mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 struct dvobj_priv* adapter_to_dvobj (TYPE_1__*) ; 
 int /*<<< orphan*/  check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rtw_get_ch_setting_union(_adapter *adapter, u8 *ch, u8 *bw, u8 *offset)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	_adapter *iface;
	struct mlme_ext_priv *mlmeext;
	int i;
	u8 ch_ret = 0;
	u8 bw_ret = HT_CHANNEL_WIDTH_20;
	u8 offset_ret = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	int num = 0;

	if (ch) *ch = 0;
	if (bw) *bw = HT_CHANNEL_WIDTH_20;
	if (offset) *offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	for (i = 0; i<dvobj->iface_nums; i++) {
		iface = dvobj->padapters[i];
		mlmeext = &iface->mlmeextpriv;

		if (!check_fwstate(&iface->mlmepriv, _FW_LINKED))
			continue;

		if (num == 0) {
			ch_ret = mlmeext->cur_channel;
			bw_ret = mlmeext->cur_bwmode;
			offset_ret = mlmeext->cur_ch_offset;
			num++;
			continue;
		}

		if (ch_ret != mlmeext->cur_channel) {
			num = 0;
			break;
		}

		if (bw_ret < mlmeext->cur_bwmode) {
			bw_ret = mlmeext->cur_bwmode;
			offset_ret = mlmeext->cur_ch_offset;
		} else if (bw_ret == mlmeext->cur_bwmode && offset_ret != mlmeext->cur_ch_offset) {
			num = 0;
			break;
		}

		num++;
	}

	if (num) {
		if (ch) *ch = ch_ret;
		if (bw) *bw = bw_ret;
		if (offset) *offset = offset_ret;
	}

	return num;
}