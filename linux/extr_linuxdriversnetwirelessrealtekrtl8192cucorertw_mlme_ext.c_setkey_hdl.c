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
struct setkey_parm {int keyid; int algorithm; int /*<<< orphan*/  key; scalar_t__ set_tx; } ;
struct mlme_ext_info {int key_index; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  HW_VAR_ON_RCR_AM ; 
 int /*<<< orphan*/  null_addr ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cam (TYPE_1__*,int,unsigned short,unsigned char*,int /*<<< orphan*/ ) ; 

u8 setkey_hdl(_adapter *padapter, u8 *pbuf)
{
	unsigned short				ctrl;
	struct setkey_parm		*pparm = (struct setkey_parm *)pbuf;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	unsigned char					null_sta[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	//main tx key for wep.
	if(pparm->set_tx)
		pmlmeinfo->key_index = pparm->keyid;
	
	//write cam
	ctrl = BIT(15) | ((pparm->algorithm) << 2) | pparm->keyid;	

	write_cam(padapter, pparm->keyid, ctrl, null_sta, pparm->key);

	//allow multicast packets to driver
	rtw_hal_set_hwreg(padapter, HW_VAR_ON_RCR_AM, null_addr);

	return H2C_SUCCESS;
}