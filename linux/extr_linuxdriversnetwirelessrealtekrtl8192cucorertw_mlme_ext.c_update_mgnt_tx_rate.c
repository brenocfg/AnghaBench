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
typedef  int /*<<< orphan*/  u8 ;
struct mlme_ext_priv {int /*<<< orphan*/  tx_rate; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */

void update_mgnt_tx_rate(_adapter *padapter, u8 rate)
{
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);

	pmlmeext->tx_rate = rate;

	//DBG_871X("%s(): rate = %x\n",__FUNCTION__, rate);
}