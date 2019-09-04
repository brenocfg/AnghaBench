#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_priv {int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_channel; } ;
struct TYPE_4__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  set_channel_bwmode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int init_hw_mlme_ext(_adapter *padapter)
{
	struct	mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	//set_opmode_cmd(padapter, infra_client_with_mlme);//removed

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	return _SUCCESS;
}