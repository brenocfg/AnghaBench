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
struct TYPE_5__ {int ATIMWindow; int /*<<< orphan*/  DSConfig; } ;
struct wlan_bssid_ex {scalar_t__ InfrastructureMode; int IELength; int /*<<< orphan*/  Length; TYPE_2__ Configuration; int /*<<< orphan*/  NetworkTypeInUse; scalar_t__ Rssi; int /*<<< orphan*/  Privacy; } ;
struct security_priv {scalar_t__ PrivacyAlgrthm; } ;
struct registry_priv {int wireless_mode; int /*<<< orphan*/  channel; struct wlan_bssid_ex dev_network; } ;
struct TYPE_4__ {struct wlan_network cur_network; } ;
struct _adapter {TYPE_1__ mlmepriv; struct security_priv securitypriv; struct registry_priv registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Ndis802_11DS ; 
 scalar_t__ Ndis802_11IBSS ; 
 int /*<<< orphan*/  Ndis802_11OFDM24 ; 
 int /*<<< orphan*/  Ndis802_11OFDM5 ; 
#define  WIRELESS_11A 131 
#define  WIRELESS_11B 130 
#define  WIRELESS_11BG 129 
#define  WIRELESS_11G 128 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int r8712_generate_ie (struct registry_priv*) ; 
 int /*<<< orphan*/  r8712_get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 

void r8712_update_registrypriv_dev_network(struct _adapter *adapter)
{
	int sz = 0;
	struct registry_priv	*pregistrypriv = &adapter->registrypriv;
	struct wlan_bssid_ex	*pdev_network = &pregistrypriv->dev_network;
	struct security_priv	*psecuritypriv = &adapter->securitypriv;
	struct wlan_network	*cur_network = &adapter->mlmepriv.cur_network;

	pdev_network->Privacy = cpu_to_le32(psecuritypriv->PrivacyAlgrthm
					    > 0 ? 1 : 0); /* adhoc no 802.1x */
	pdev_network->Rssi = 0;
	switch (pregistrypriv->wireless_mode) {
	case WIRELESS_11B:
		pdev_network->NetworkTypeInUse = Ndis802_11DS;
		break;
	case WIRELESS_11G:
	case WIRELESS_11BG:
		pdev_network->NetworkTypeInUse = Ndis802_11OFDM24;
		break;
	case WIRELESS_11A:
		pdev_network->NetworkTypeInUse = Ndis802_11OFDM5;
		break;
	default:
		/* TODO */
		break;
	}
	pdev_network->Configuration.DSConfig = pregistrypriv->channel;
	if (cur_network->network.InfrastructureMode == Ndis802_11IBSS)
		pdev_network->Configuration.ATIMWindow = 3;
	pdev_network->InfrastructureMode = cur_network->network.InfrastructureMode;
	/* 1. Supported rates
	 * 2. IE
	 */
	sz = r8712_generate_ie(pregistrypriv);
	pdev_network->IELength = sz;
	pdev_network->Length = r8712_get_wlan_bssid_ex_sz(pdev_network);
}