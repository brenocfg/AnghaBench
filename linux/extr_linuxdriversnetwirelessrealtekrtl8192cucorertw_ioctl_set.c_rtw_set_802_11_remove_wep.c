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
typedef  int u8 ;
typedef  int u32 ;
struct security_priv {scalar_t__* dot11DefKeylen; int /*<<< orphan*/ * dot11DefKey; } ;
struct TYPE_4__ {struct security_priv securitypriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int _FAIL ; 
 int _FALSE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rtw_set_key (TYPE_1__*,struct security_priv*,int,int /*<<< orphan*/ ) ; 

u8 rtw_set_802_11_remove_wep(_adapter* padapter, u32 keyindex){
	
	u8 ret=_SUCCESS;
	
_func_enter_;

	if (keyindex >= 0x80000000 || padapter == NULL){
		
		ret=_FALSE;
		goto exit;

	}
	else 
	{
		int res;
		struct security_priv* psecuritypriv=&(padapter->securitypriv);
		if( keyindex < 4 ){
			
			_rtw_memset(&psecuritypriv->dot11DefKey[keyindex], 0, 16);
			
			res=rtw_set_key(padapter,psecuritypriv,keyindex, 0);
			
			psecuritypriv->dot11DefKeylen[keyindex]=0;
			
			if(res==_FAIL)
				ret=_FAIL;
			
		}
		else
		{			
			ret=_FAIL;
		}
		
	}
	
exit:	
	
_func_exit_;

	return ret;
	
}