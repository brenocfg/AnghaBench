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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ DwellTime; scalar_t__ HopSet; scalar_t__ HopPattern; scalar_t__ Length; } ;
struct TYPE_4__ {int Length; int BeaconPeriod; TYPE_1__ FHConfig; } ;
struct wlan_bssid_ex {TYPE_2__ Configuration; int /*<<< orphan*/  Ssid; int /*<<< orphan*/ * MacAddress; } ;
struct registry_priv {int /*<<< orphan*/  ssid; struct wlan_bssid_ex dev_network; } ;
struct ndis_802_11_ssid {int dummy; } ;
struct eeprom_priv {int dummy; } ;
struct _adapter {struct eeprom_priv eeprompriv; struct registry_priv registrypriv; } ;
struct NDIS_802_11_CONFIGURATION {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * myid (struct eeprom_priv*) ; 

void r8712_init_registrypriv_dev_network(struct _adapter *adapter)
{
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
	struct eeprom_priv *peepriv = &adapter->eeprompriv;
	struct wlan_bssid_ex *pdev_network = &pregistrypriv->dev_network;
	u8 *myhwaddr = myid(peepriv);

	memcpy(pdev_network->MacAddress, myhwaddr, ETH_ALEN);
	memcpy(&pdev_network->Ssid, &pregistrypriv->ssid,
		sizeof(struct ndis_802_11_ssid));
	pdev_network->Configuration.Length =
			 sizeof(struct NDIS_802_11_CONFIGURATION);
	pdev_network->Configuration.BeaconPeriod = 100;
	pdev_network->Configuration.FHConfig.Length = 0;
	pdev_network->Configuration.FHConfig.HopPattern = 0;
	pdev_network->Configuration.FHConfig.HopSet = 0;
	pdev_network->Configuration.FHConfig.DwellTime = 0;
}