#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_2__ data; TYPE_1__ src_addr; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct security_priv {scalar_t__ last_mic_err_time; int btkip_countermeasure_time; int /*<<< orphan*/  btkip_countermeasure; } ;
struct mlme_priv {int /*<<< orphan*/ * assoc_bssid; } ;
struct iw_michaelmicfailure {TYPE_2__ data; TYPE_1__ src_addr; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ev ;
struct TYPE_7__ {int /*<<< orphan*/  pnetdev; struct security_priv securitypriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int HZ ; 
 int /*<<< orphan*/  IWEVMICHAELMICFAILURE ; 
 int /*<<< orphan*/  IW_MICFAILURE_GROUP ; 
 int /*<<< orphan*/  IW_MICFAILURE_PAIRWISE ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memset (union iwreq_data*,int,int) ; 
 void* rtw_get_current_time () ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,char*) ; 

void rtw_handle_tkip_mic_err(_adapter *padapter,u8 bgroup)
{
#ifdef CONFIG_IOCTL_CFG80211
	enum nl80211_key_type key_type = 0;
#endif
	union iwreq_data wrqu;
	struct iw_michaelmicfailure    ev;
	struct mlme_priv*              pmlmepriv  = &padapter->mlmepriv;
	struct security_priv	*psecuritypriv = &padapter->securitypriv;	
	u32 cur_time = 0;

	if( psecuritypriv->last_mic_err_time == 0 )
	{
		psecuritypriv->last_mic_err_time = rtw_get_current_time();
	}
	else
	{
		cur_time = rtw_get_current_time();

		if( cur_time - psecuritypriv->last_mic_err_time < 60*HZ )
		{
			psecuritypriv->btkip_countermeasure = _TRUE;
			psecuritypriv->last_mic_err_time = 0;
			psecuritypriv->btkip_countermeasure_time = cur_time;
		}
		else
		{
			psecuritypriv->last_mic_err_time = rtw_get_current_time();
		}
	}

#ifdef CONFIG_IOCTL_CFG80211
	if ( bgroup )
	{
		key_type |= NL80211_KEYTYPE_GROUP;
	}
	else
	{
		key_type |= NL80211_KEYTYPE_PAIRWISE;
	}

	cfg80211_michael_mic_failure(padapter->pnetdev, (u8 *)&pmlmepriv->assoc_bssid[ 0 ], key_type, -1,
		NULL, GFP_ATOMIC);
#endif

	_rtw_memset( &ev, 0x00, sizeof( ev ) );
	if ( bgroup )
	{
	    ev.flags |= IW_MICFAILURE_GROUP;
	}
	else
	{
	    ev.flags |= IW_MICFAILURE_PAIRWISE;
	}

	ev.src_addr.sa_family = ARPHRD_ETHER;
	_rtw_memcpy( ev.src_addr.sa_data, &pmlmepriv->assoc_bssid[ 0 ], ETH_ALEN );

	_rtw_memset( &wrqu, 0x00, sizeof( wrqu ) );
	wrqu.data.length = sizeof( ev );

	wireless_send_event( padapter->pnetdev, IWEVMICHAELMICFAILURE, &wrqu, (char*) &ev );
}