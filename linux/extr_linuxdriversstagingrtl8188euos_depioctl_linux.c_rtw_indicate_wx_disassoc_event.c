#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct adapter {int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  DBG_88E_LEVEL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  _drv_always_ ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void rtw_indicate_wx_disassoc_event(struct adapter *padapter)
{
	union iwreq_data wrqu;

	memset(&wrqu, 0, sizeof(union iwreq_data));

	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	eth_zero_addr(wrqu.ap_addr.sa_data);

	DBG_88E_LEVEL(_drv_always_, "indicate disassoc\n");
	wireless_send_event(padapter->pnetdev, SIOCGIWAP, &wrqu, NULL);
}