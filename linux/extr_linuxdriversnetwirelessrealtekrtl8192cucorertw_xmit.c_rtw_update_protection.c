#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int u8 ;
struct xmit_priv {int vcs_setting; void* vcs; } ;
struct registry_priv {void* vcs_type; } ;
typedef  int /*<<< orphan*/  sint ;
struct TYPE_3__ {struct registry_priv registrypriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
#define  AUTO_VCS 130 
 int BIT (int) ; 
 void* CTS_TO_SELF ; 
#define  DISABLE_VCS 129 
#define  ENABLE_VCS 128 
 void* NONE_VCS ; 
 void* RTS_CTS ; 
 int /*<<< orphan*/  _ERPINFO_IE_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int* rtw_get_ie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void rtw_update_protection(_adapter *padapter, u8 *ie, uint ie_len)
{

	uint	protection;
	u8	*perp;
	sint	 erp_len;
	struct	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct	registry_priv *pregistrypriv = &padapter->registrypriv;
	
_func_enter_;
	
	switch(pxmitpriv->vcs_setting)
	{
		case DISABLE_VCS:
			pxmitpriv->vcs = NONE_VCS;
			break;
	
		case ENABLE_VCS:
			break;
	
		case AUTO_VCS:
		default:
			perp = rtw_get_ie(ie, _ERPINFO_IE_, &erp_len, ie_len);
			if(perp == NULL)
			{
				pxmitpriv->vcs = NONE_VCS;
			}
			else
			{
				protection = (*(perp + 2)) & BIT(1);
				if (protection)
				{
					if(pregistrypriv->vcs_type == RTS_CTS)
						pxmitpriv->vcs = RTS_CTS;
					else
						pxmitpriv->vcs = CTS_TO_SELF;
				}
				else
					pxmitpriv->vcs = NONE_VCS;
			}

			break;			
	
	}

_func_exit_;

}