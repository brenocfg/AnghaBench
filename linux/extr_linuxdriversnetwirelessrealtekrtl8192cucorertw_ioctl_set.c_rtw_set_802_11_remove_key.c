#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int u8 ;
struct sta_info {int /*<<< orphan*/  dot118021x_UncstKey; int /*<<< orphan*/  dot118021XPrivacy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dot118021XGrpKey; int /*<<< orphan*/  dot118021XGrpPrivacy; } ;
struct TYPE_7__ {int /*<<< orphan*/  stapriv; int /*<<< orphan*/  mlmepriv; TYPE_1__ securitypriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_8__ {int KeyIndex; } ;
typedef  TYPE_3__ NDIS_802_11_REMOVE_KEY ;

/* Variables and functions */
 int _FAIL ; 
 int _FALSE ; 
 int _SUCCESS ; 
 int _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* get_bssid (int /*<<< orphan*/ *) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int*) ; 

u8 rtw_set_802_11_remove_key(_adapter*	padapter, NDIS_802_11_REMOVE_KEY *key){
	
	uint				encryptionalgo;
	u8 * pbssid;
	struct sta_info *stainfo;
	u8	bgroup = (key->KeyIndex & 0x4000000) > 0 ? _FALSE: _TRUE;
	u8	keyIndex = (u8)key->KeyIndex & 0x03;
	u8	ret=_SUCCESS;
	
_func_enter_;

	if ((key->KeyIndex & 0xbffffffc) > 0) {
		ret=_FAIL;
		goto exit;
	}

	if (bgroup == _TRUE) {
		encryptionalgo= padapter->securitypriv.dot118021XGrpPrivacy;
		// clear group key by index
		//NdisZeroMemory(Adapter->MgntInfo.SecurityInfo.KeyBuf[keyIndex], MAX_WEP_KEY_LEN);
		//Adapter->MgntInfo.SecurityInfo.KeyLen[keyIndex] = 0;
		
		_rtw_memset(&padapter->securitypriv.dot118021XGrpKey[keyIndex], 0, 16);
		
		//! \todo Send a H2C Command to Firmware for removing this Key in CAM Entry.
	
	} else {
	
		pbssid=get_bssid(&padapter->mlmepriv);
		stainfo=rtw_get_stainfo(&padapter->stapriv , pbssid );
		if(stainfo !=NULL){
			encryptionalgo=stainfo->dot118021XPrivacy;

		// clear key by BSSID
		_rtw_memset(&stainfo->dot118021x_UncstKey, 0, 16);
		
		//! \todo Send a H2C Command to Firmware for disable this Key in CAM Entry.

		}
		else{
			ret= _FAIL;
			goto exit;
		}
	}

exit:
	
_func_exit_;

	return _TRUE;
	
}