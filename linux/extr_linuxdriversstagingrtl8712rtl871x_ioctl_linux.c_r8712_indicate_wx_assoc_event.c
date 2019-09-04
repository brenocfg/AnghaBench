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
struct TYPE_4__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_6__ {TYPE_2__ network; } ;
struct mlme_priv {TYPE_3__ cur_network; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void r8712_indicate_wx_assoc_event(struct _adapter *padapter)
{
	union iwreq_data wrqu;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	memcpy(wrqu.ap_addr.sa_data, pmlmepriv->cur_network.network.MacAddress,
		ETH_ALEN);
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, NULL);
}