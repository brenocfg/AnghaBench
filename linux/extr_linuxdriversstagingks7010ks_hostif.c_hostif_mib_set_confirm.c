#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  snooze_guard; } ;
struct TYPE_3__ {int /*<<< orphan*/  rsn_enabled; int /*<<< orphan*/  wpa_enabled; } ;
struct ks_wlan_private {int mac_address_valid; TYPE_2__ psstatus; TYPE_1__ wpa; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
#define  DOT11_FRAGMENTATION_THRESHOLD 151 
#define  DOT11_GMK1_TSC 150 
#define  DOT11_GMK2_TSC 149 
#define  DOT11_PMK_TSC 148 
#define  DOT11_PRIVACY_INVOKED 147 
#define  DOT11_RSN_CONFIG_AUTH_SUITE 146 
#define  DOT11_RSN_CONFIG_MULTICAST_CIPHER 145 
#define  DOT11_RSN_CONFIG_UNICAST_CIPHER 144 
#define  DOT11_RSN_ENABLED 143 
#define  DOT11_RTS_THRESHOLD 142 
#define  DOT11_WEP_DEFAULT_KEY_ID 141 
#define  DOT11_WEP_DEFAULT_KEY_VALUE1 140 
#define  DOT11_WEP_DEFAULT_KEY_VALUE2 139 
#define  DOT11_WEP_DEFAULT_KEY_VALUE3 138 
#define  DOT11_WEP_DEFAULT_KEY_VALUE4 137 
#define  LOCAL_CURRENTADDRESS 136 
#define  LOCAL_GAIN 135 
#define  LOCAL_MULTICAST_ADDRESS 134 
#define  LOCAL_MULTICAST_FILTER 133 
#define  LOCAL_PMK 132 
#define  LOCAL_REGION 131 
#define  LOCAL_RSN_MODE 130 
#define  LOCAL_WPS_ENABLE 129 
#define  LOCAL_WPS_PROBE_REQ 128 
 int /*<<< orphan*/  SME_FRAGMENTATION_THRESHOLD_CONFIRM ; 
 int /*<<< orphan*/  SME_MULTICAST_CONFIRM ; 
 int /*<<< orphan*/  SME_MULTICAST_REQUEST ; 
 int /*<<< orphan*/  SME_RSN_AUTH_CONFIRM ; 
 int /*<<< orphan*/  SME_RSN_ENABLED_CONFIRM ; 
 int /*<<< orphan*/  SME_RSN_MCAST_CONFIRM ; 
 int /*<<< orphan*/  SME_RSN_MODE_CONFIRM ; 
 int /*<<< orphan*/  SME_RSN_UCAST_CONFIRM ; 
 int /*<<< orphan*/  SME_RTS_THRESHOLD_CONFIRM ; 
 int /*<<< orphan*/  SME_SET_GMK1_TSC ; 
 int /*<<< orphan*/  SME_SET_GMK2_TSC ; 
 int /*<<< orphan*/  SME_SET_PMK_TSC ; 
 int /*<<< orphan*/  SME_WEP_FLAG_CONFIRM ; 
 int /*<<< orphan*/  SME_WEP_INDEX_CONFIRM ; 
 int /*<<< orphan*/  SME_WEP_KEY1_CONFIRM ; 
 int /*<<< orphan*/  SME_WEP_KEY2_CONFIRM ; 
 int /*<<< orphan*/  SME_WEP_KEY3_CONFIRM ; 
 int /*<<< orphan*/  SME_WEP_KEY4_CONFIRM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_dword (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static
void hostif_mib_set_confirm(struct ks_wlan_private *priv)
{
	u32 mib_status;
	u32 mib_attribute;

	mib_status = get_dword(priv);
	mib_attribute = get_dword(priv);

	if (mib_status) {
		/* in case of error */
		netdev_err(priv->net_dev, "error :: attribute=%08X, status=%08X\n",
			   mib_attribute, mib_status);
	}

	switch (mib_attribute) {
	case DOT11_RTS_THRESHOLD:
		hostif_sme_enqueue(priv, SME_RTS_THRESHOLD_CONFIRM);
		break;
	case DOT11_FRAGMENTATION_THRESHOLD:
		hostif_sme_enqueue(priv, SME_FRAGMENTATION_THRESHOLD_CONFIRM);
		break;
	case DOT11_WEP_DEFAULT_KEY_ID:
		if (!priv->wpa.wpa_enabled)
			hostif_sme_enqueue(priv, SME_WEP_INDEX_CONFIRM);
		break;
	case DOT11_WEP_DEFAULT_KEY_VALUE1:
		if (priv->wpa.rsn_enabled)
			hostif_sme_enqueue(priv, SME_SET_PMK_TSC);
		else
			hostif_sme_enqueue(priv, SME_WEP_KEY1_CONFIRM);
		break;
	case DOT11_WEP_DEFAULT_KEY_VALUE2:
		if (priv->wpa.rsn_enabled)
			hostif_sme_enqueue(priv, SME_SET_GMK1_TSC);
		else
			hostif_sme_enqueue(priv, SME_WEP_KEY2_CONFIRM);
		break;
	case DOT11_WEP_DEFAULT_KEY_VALUE3:
		if (priv->wpa.rsn_enabled)
			hostif_sme_enqueue(priv, SME_SET_GMK2_TSC);
		else
			hostif_sme_enqueue(priv, SME_WEP_KEY3_CONFIRM);
		break;
	case DOT11_WEP_DEFAULT_KEY_VALUE4:
		if (!priv->wpa.rsn_enabled)
			hostif_sme_enqueue(priv, SME_WEP_KEY4_CONFIRM);
		break;
	case DOT11_PRIVACY_INVOKED:
		if (!priv->wpa.rsn_enabled)
			hostif_sme_enqueue(priv, SME_WEP_FLAG_CONFIRM);
		break;
	case DOT11_RSN_ENABLED:
		hostif_sme_enqueue(priv, SME_RSN_ENABLED_CONFIRM);
		break;
	case LOCAL_RSN_MODE:
		hostif_sme_enqueue(priv, SME_RSN_MODE_CONFIRM);
		break;
	case LOCAL_MULTICAST_ADDRESS:
		hostif_sme_enqueue(priv, SME_MULTICAST_REQUEST);
		break;
	case LOCAL_MULTICAST_FILTER:
		hostif_sme_enqueue(priv, SME_MULTICAST_CONFIRM);
		break;
	case LOCAL_CURRENTADDRESS:
		priv->mac_address_valid = true;
		break;
	case DOT11_RSN_CONFIG_MULTICAST_CIPHER:
		hostif_sme_enqueue(priv, SME_RSN_MCAST_CONFIRM);
		break;
	case DOT11_RSN_CONFIG_UNICAST_CIPHER:
		hostif_sme_enqueue(priv, SME_RSN_UCAST_CONFIRM);
		break;
	case DOT11_RSN_CONFIG_AUTH_SUITE:
		hostif_sme_enqueue(priv, SME_RSN_AUTH_CONFIRM);
		break;
	case DOT11_GMK1_TSC:
		if (atomic_read(&priv->psstatus.snooze_guard))
			atomic_set(&priv->psstatus.snooze_guard, 0);
		break;
	case DOT11_GMK2_TSC:
		if (atomic_read(&priv->psstatus.snooze_guard))
			atomic_set(&priv->psstatus.snooze_guard, 0);
		break;
	case DOT11_PMK_TSC:
	case LOCAL_PMK:
	case LOCAL_GAIN:
	case LOCAL_WPS_ENABLE:
	case LOCAL_WPS_PROBE_REQ:
	case LOCAL_REGION:
	default:
		break;
	}
}