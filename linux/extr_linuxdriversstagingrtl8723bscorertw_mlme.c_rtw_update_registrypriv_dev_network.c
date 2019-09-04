#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ InfrastructureMode; } ;
struct wlan_network {TYPE_3__ network; } ;
struct TYPE_5__ {int DSConfig; int /*<<< orphan*/  ATIMWindow; } ;
struct wlan_bssid_ex {int Privacy; scalar_t__ InfrastructureMode; int IELength; int /*<<< orphan*/  Length; TYPE_2__ Configuration; void* NetworkTypeInUse; scalar_t__ Rssi; } ;
struct security_priv {scalar_t__ dot11PrivacyAlgrthm; } ;
struct registry_priv {int wireless_mode; int channel; struct wlan_bssid_ex dev_network; } ;
struct TYPE_4__ {struct wlan_network cur_network; } ;
struct adapter {TYPE_1__ mlmepriv; struct security_priv securitypriv; struct registry_priv registrypriv; } ;

/* Variables and functions */
 void* Ndis802_11DS ; 
 scalar_t__ Ndis802_11IBSS ; 
 void* Ndis802_11OFDM24 ; 
 void* Ndis802_11OFDM5 ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  WIRELESS_11A 136 
#define  WIRELESS_11ABGN 135 
#define  WIRELESS_11A_5N 134 
#define  WIRELESS_11B 133 
#define  WIRELESS_11BG 132 
#define  WIRELESS_11BG_24N 131 
#define  WIRELESS_11G 130 
#define  WIRELESS_11G_24N 129 
#define  WIRELESS_11_24N 128 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 
 int rtw_generate_ie (struct registry_priv*) ; 

void rtw_update_registrypriv_dev_network(struct adapter *adapter)
{
	int sz = 0;
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
	struct wlan_bssid_ex    *pdev_network = &pregistrypriv->dev_network;
	struct	security_priv *psecuritypriv = &adapter->securitypriv;
	struct	wlan_network	*cur_network = &adapter->mlmepriv.cur_network;
	/* struct	xmit_priv *pxmitpriv = &adapter->xmitpriv; */

	pdev_network->Privacy = (psecuritypriv->dot11PrivacyAlgrthm > 0 ? 1 : 0) ; /*  adhoc no 802.1x */

	pdev_network->Rssi = 0;

	switch (pregistrypriv->wireless_mode) {
	case WIRELESS_11B:
		pdev_network->NetworkTypeInUse = (Ndis802_11DS);
		break;
	case WIRELESS_11G:
	case WIRELESS_11BG:
	case WIRELESS_11_24N:
	case WIRELESS_11G_24N:
	case WIRELESS_11BG_24N:
		pdev_network->NetworkTypeInUse = (Ndis802_11OFDM24);
		break;
	case WIRELESS_11A:
	case WIRELESS_11A_5N:
		pdev_network->NetworkTypeInUse = (Ndis802_11OFDM5);
		break;
	case WIRELESS_11ABGN:
		if (pregistrypriv->channel > 14)
			pdev_network->NetworkTypeInUse = (Ndis802_11OFDM5);
		else
			pdev_network->NetworkTypeInUse = (Ndis802_11OFDM24);
		break;
	default:
		/*  TODO */
		break;
	}

	pdev_network->Configuration.DSConfig = (pregistrypriv->channel);
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("pregistrypriv->channel =%d, pdev_network->Configuration.DSConfig = 0x%x\n", pregistrypriv->channel, pdev_network->Configuration.DSConfig));

	if (cur_network->network.InfrastructureMode == Ndis802_11IBSS)
		pdev_network->Configuration.ATIMWindow = (0);

	pdev_network->InfrastructureMode = (cur_network->network.InfrastructureMode);

	/*  1. Supported rates */
	/*  2. IE */

	/* rtw_set_supported_rate(pdev_network->SupportedRates, pregistrypriv->wireless_mode) ;  will be called in rtw_generate_ie */
	sz = rtw_generate_ie(pregistrypriv);

	pdev_network->IELength = sz;

	pdev_network->Length = get_wlan_bssid_ex_sz((struct wlan_bssid_ex  *)pdev_network);

	/* notes: translate IELength & Length after assign the Length to cmdsz in createbss_cmd(); */
	/* pdev_network->IELength = cpu_to_le32(sz); */
}