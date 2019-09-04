#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_8__ {int /*<<< orphan*/  skey; } ;
struct TYPE_6__ {int /*<<< orphan*/  skey; } ;
struct sta_info {int ieee8021x_blocked; TYPE_4__ dot118021x_UncstKey; int /*<<< orphan*/  dot11txpn; TYPE_2__ dot11tkiptxmickey; int /*<<< orphan*/  mac_id; } ;
struct security_priv {int dot11AuthAlgrthm; int sw_encrypt; int hw_decrypted; int /*<<< orphan*/  busetkipkey; int /*<<< orphan*/  dot118021XGrpKeyid; int /*<<< orphan*/  dot11PrivacyKeyIndex; } ;
struct TYPE_7__ {int /*<<< orphan*/  skey; } ;
struct TYPE_5__ {int /*<<< orphan*/  skey; } ;
struct pkt_attrib {int encrypt; int ether_type; int iv_len; int icv_len; int bswenc; TYPE_3__ dot118021x_UncstKey; int /*<<< orphan*/  iv; void* key_idx; TYPE_1__ dot11tkiptxmickey; int /*<<< orphan*/  mac_id; int /*<<< orphan*/  ra; } ;
struct mlme_priv {int dummy; } ;
struct adapter {struct security_priv securitypriv; struct mlme_priv mlmepriv; } ;
typedef  int /*<<< orphan*/  sint ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AES_IV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  GET_ENCRY_ALGO (struct security_priv*,struct sta_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_MCAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TKIP_IV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  WEP_IV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
#define  _AES_ 135 
 int /*<<< orphan*/  _FAIL ; 
 int _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _SUCCESS ; 
#define  _TKIP_ 134 
#define  _WEP104_ 133 
#define  _WEP40_ 132 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
#define  dot11AuthAlgrthm_8021X 131 
#define  dot11AuthAlgrthm_Auto 130 
#define  dot11AuthAlgrthm_Open 129 
#define  dot11AuthAlgrthm_Shared 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 update_attrib_sec_info(struct adapter *padapter, struct pkt_attrib *pattrib, struct sta_info *psta)
{
	sint res = _SUCCESS;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	sint bmcast = IS_MCAST(pattrib->ra);

	memset(pattrib->dot118021x_UncstKey.skey,  0, 16);
	memset(pattrib->dot11tkiptxmickey.skey,  0, 16);
	pattrib->mac_id = psta->mac_id;

	if (psta->ieee8021x_blocked == true) {
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("\n psta->ieee8021x_blocked == true\n"));

		pattrib->encrypt = 0;

		if ((pattrib->ether_type != 0x888e) && (check_fwstate(pmlmepriv, WIFI_MP_STATE) == false)) {
			RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("\npsta->ieee8021x_blocked == true,  pattrib->ether_type(%.4x) != 0x888e\n", pattrib->ether_type));
			#ifdef DBG_TX_DROP_FRAME
			DBG_871X("DBG_TX_DROP_FRAME %s psta->ieee8021x_blocked == true,  pattrib->ether_type(%04x) != 0x888e\n", __func__, pattrib->ether_type);
			#endif
			res = _FAIL;
			goto exit;
		}
	} else{
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, bmcast);

		switch (psecuritypriv->dot11AuthAlgrthm) {
		case dot11AuthAlgrthm_Open:
		case dot11AuthAlgrthm_Shared:
		case dot11AuthAlgrthm_Auto:
			pattrib->key_idx = (u8)psecuritypriv->dot11PrivacyKeyIndex;
			break;
		case dot11AuthAlgrthm_8021X:
			if (bmcast)
				pattrib->key_idx = (u8)psecuritypriv->dot118021XGrpKeyid;
			else
				pattrib->key_idx = 0;
			break;
		default:
			pattrib->key_idx = 0;
			break;
		}

		/* For WPS 1.0 WEP, driver should not encrypt EAPOL Packet for WPS handshake. */
		if (((pattrib->encrypt == _WEP40_) || (pattrib->encrypt == _WEP104_)) && (pattrib->ether_type == 0x888e))
			pattrib->encrypt = _NO_PRIVACY_;

	}

	switch (pattrib->encrypt) {
	case _WEP40_:
	case _WEP104_:
		pattrib->iv_len = 4;
		pattrib->icv_len = 4;
		WEP_IV(pattrib->iv, psta->dot11txpn, pattrib->key_idx);
		break;

	case _TKIP_:
		pattrib->iv_len = 8;
		pattrib->icv_len = 4;

		if (psecuritypriv->busetkipkey == _FAIL) {
			#ifdef DBG_TX_DROP_FRAME
			DBG_871X("DBG_TX_DROP_FRAME %s psecuritypriv->busetkipkey(%d) == _FAIL drop packet\n", __func__, psecuritypriv->busetkipkey);
			#endif
			res = _FAIL;
			goto exit;
		}

		if (bmcast)
			TKIP_IV(pattrib->iv, psta->dot11txpn, pattrib->key_idx);
		else
			TKIP_IV(pattrib->iv, psta->dot11txpn, 0);


		memcpy(pattrib->dot11tkiptxmickey.skey, psta->dot11tkiptxmickey.skey, 16);

		break;

	case _AES_:

		pattrib->iv_len = 8;
		pattrib->icv_len = 8;

		if (bmcast)
			AES_IV(pattrib->iv, psta->dot11txpn, pattrib->key_idx);
		else
			AES_IV(pattrib->iv, psta->dot11txpn, 0);

		break;

	default:
		pattrib->iv_len = 0;
		pattrib->icv_len = 0;
		break;
	}

	if (pattrib->encrypt > 0)
		memcpy(pattrib->dot118021x_UncstKey.skey, psta->dot118021x_UncstKey.skey, 16);

	RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
		("update_attrib: encrypt =%d  securitypriv.sw_encrypt =%d\n",
		pattrib->encrypt, padapter->securitypriv.sw_encrypt));

	if (pattrib->encrypt &&
		((padapter->securitypriv.sw_encrypt == true) || (psecuritypriv->hw_decrypted == false))) {
		pattrib->bswenc = true;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
			("update_attrib: encrypt =%d securitypriv.hw_decrypted =%d bswenc =true\n",
			pattrib->encrypt, padapter->securitypriv.sw_encrypt));
	} else {
		pattrib->bswenc = false;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("update_attrib: bswenc =false\n"));
	}

exit:

	return res;

}