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
struct setauth_parm {int mode; } ;
struct mlme_ext_info {int auth_algo; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_SUCCESS ; 

u8 setauth_hdl(_adapter *padapter, unsigned char *pbuf)
{
	struct setauth_parm		*pparm = (struct setauth_parm *)pbuf;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	
	if (pparm->mode < 4)
	{
		pmlmeinfo->auth_algo = pparm->mode;
	}

	return 	H2C_SUCCESS;
}