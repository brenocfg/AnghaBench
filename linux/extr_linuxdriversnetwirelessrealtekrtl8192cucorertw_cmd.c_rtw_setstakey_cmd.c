#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sta_info {int /*<<< orphan*/  dot118021x_UncstKey; int /*<<< orphan*/ * hwaddr; } ;
struct set_stakey_rsp {int dummy; } ;
struct set_stakey_parm {unsigned char algorithm; int /*<<< orphan*/  key; int /*<<< orphan*/ * addr; } ;
struct security_priv {size_t dot118021XGrpKeyid; scalar_t__ busetkipkey; TYPE_1__* dot118021XGrpKey; scalar_t__ dot11PrivacyAlgrthm; } ;
struct mlme_priv {int dummy; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {scalar_t__* rsp; int rspsz; } ;
struct TYPE_5__ {struct security_priv securitypriv; struct mlme_priv mlmepriv; struct cmd_priv cmdpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_4__ {int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  GET_ENCRY_ALGO (struct security_priv*,struct sta_info*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _SetStaKey_CMD_ ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct set_stakey_parm*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__*,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setstakey_cmd(_adapter *padapter, u8 *psta, u8 unicast_key)
{
	struct cmd_obj*			ph2c;
	struct set_stakey_parm	*psetstakey_para;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;
	struct set_stakey_rsp		*psetstakey_rsp = NULL;
	
	struct mlme_priv			*pmlmepriv = &padapter->mlmepriv;
	struct security_priv 		*psecuritypriv = &padapter->securitypriv;
	struct sta_info* 			sta = (struct sta_info* )psta;
	u8	res=_SUCCESS;

_func_enter_;

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if ( ph2c == NULL){
		res= _FAIL;
		goto exit;
	}

	psetstakey_para = (struct set_stakey_parm*)rtw_zmalloc(sizeof(struct set_stakey_parm));
	if(psetstakey_para==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res=_FAIL;
		goto exit;
	}

	psetstakey_rsp = (struct set_stakey_rsp*)rtw_zmalloc(sizeof(struct set_stakey_rsp)); 
	if(psetstakey_rsp == NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		rtw_mfree((u8 *) psetstakey_para, sizeof(struct set_stakey_parm));
		res=_FAIL;
		goto exit;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
	ph2c->rsp = (u8 *) psetstakey_rsp;
	ph2c->rspsz = sizeof(struct set_stakey_rsp);

	_rtw_memcpy(psetstakey_para->addr, sta->hwaddr,ETH_ALEN);
	
	if(check_fwstate(pmlmepriv, WIFI_STATION_STATE)){
#ifdef CONFIG_TDLS		
		if(sta->tdls_sta_state&TDLS_LINKED_STATE)
			psetstakey_para->algorithm=(u8)sta->dot118021XPrivacy;
		else
#endif //CONFIG_TDLS
		psetstakey_para->algorithm =(unsigned char) psecuritypriv->dot11PrivacyAlgrthm;
	}else{
		GET_ENCRY_ALGO(psecuritypriv, sta, psetstakey_para->algorithm, _FALSE);
	}

	if (unicast_key == _TRUE) {
#ifdef CONFIG_TDLS
		if(sta->tdls_sta_state&TDLS_LINKED_STATE)
			_rtw_memcpy(&psetstakey_para->key, sta->tpk.tk, 16);
		else
#endif //CONFIG_TDLS
			_rtw_memcpy(&psetstakey_para->key, &sta->dot118021x_UncstKey, 16);
        } else {
		_rtw_memcpy(&psetstakey_para->key, &psecuritypriv->dot118021XGrpKey[psecuritypriv->dot118021XGrpKeyid].skey, 16);
        }

	//jeff: set this becasue at least sw key is ready
	padapter->securitypriv.busetkipkey=_TRUE;

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	

exit:

_func_exit_;	

	return res;
}