#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  chk_bmc_sleepq_hdl (struct adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ send_beacon (struct adapter*) ; 

u8 tx_beacon_hdl(struct adapter *padapter, unsigned char *pbuf)
{
	if (send_beacon(padapter) == _FAIL) {
		DBG_871X("issue_beacon, fail!\n");
		return H2C_PARAMETERS_ERROR;
	}

	/* tx bc/mc frames after update TIM */
	chk_bmc_sleepq_hdl(padapter, NULL);

	return H2C_SUCCESS;
}