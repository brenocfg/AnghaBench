#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ DwellTime; scalar_t__ HopSet; scalar_t__ HopPattern; scalar_t__ Length; } ;
struct TYPE_7__ {int Length; int BeaconPeriod; TYPE_1__ FHConfig; } ;
struct TYPE_9__ {TYPE_2__ Configuration; int /*<<< orphan*/  Ssid; int /*<<< orphan*/ * MacAddress; } ;
struct registry_priv {int /*<<< orphan*/  ssid; TYPE_4__ dev_network; } ;
struct eeprom_priv {int dummy; } ;
struct TYPE_8__ {struct eeprom_priv eeprompriv; struct registry_priv registrypriv; } ;
typedef  TYPE_3__ _adapter ;
typedef  TYPE_4__ WLAN_BSSID_EX ;
typedef  int /*<<< orphan*/  NDIS_802_11_SSID ;
typedef  int /*<<< orphan*/  NDIS_802_11_CONFIGURATION ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * myid (struct eeprom_priv*) ; 

void rtw_init_registrypriv_dev_network(	_adapter* adapter)
{
	struct registry_priv* pregistrypriv = &adapter->registrypriv;
	struct eeprom_priv* peepriv = &adapter->eeprompriv;
	WLAN_BSSID_EX    *pdev_network = &pregistrypriv->dev_network;
	u8 *myhwaddr = myid(peepriv);
	
_func_enter_;

	_rtw_memcpy(pdev_network->MacAddress, myhwaddr, ETH_ALEN);

	_rtw_memcpy(&pdev_network->Ssid, &pregistrypriv->ssid, sizeof(NDIS_802_11_SSID));
	
	pdev_network->Configuration.Length=sizeof(NDIS_802_11_CONFIGURATION);
	pdev_network->Configuration.BeaconPeriod = 100;	
	pdev_network->Configuration.FHConfig.Length = 0;
	pdev_network->Configuration.FHConfig.HopPattern = 0;
	pdev_network->Configuration.FHConfig.HopSet = 0;
	pdev_network->Configuration.FHConfig.DwellTime = 0;
	
	
_func_exit_;	
	
}