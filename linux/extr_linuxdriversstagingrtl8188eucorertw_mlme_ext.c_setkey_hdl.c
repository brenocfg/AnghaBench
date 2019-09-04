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
typedef  int /*<<< orphan*/  u8 ;
struct setkey_parm {int keyid; int algorithm; int /*<<< orphan*/  key; scalar_t__ set_tx; } ;
struct mlme_ext_info {int key_index; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_88E_LEVEL (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  write_cam (struct adapter*,int,unsigned short,unsigned char*,int /*<<< orphan*/ ) ; 

u8 setkey_hdl(struct adapter *padapter, u8 *pbuf)
{
	unsigned short				ctrl;
	struct setkey_parm		*pparm = (struct setkey_parm *)pbuf;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	unsigned char					null_sta[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	/* main tx key for wep. */
	if (pparm->set_tx)
		pmlmeinfo->key_index = pparm->keyid;

	/* write cam */
	ctrl = BIT(15) | ((pparm->algorithm) << 2) | pparm->keyid;

	DBG_88E_LEVEL(_drv_info_, "set group key to hw: alg:%d(WEP40-1 WEP104-5 TKIP-2 AES-4) "
			"keyid:%d\n", pparm->algorithm, pparm->keyid);
	write_cam(padapter, pparm->keyid, ctrl, null_sta, pparm->key);

	return H2C_SUCCESS;
}