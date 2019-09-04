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
struct mlme_priv {int dummy; } ;
struct cmd_obj {scalar_t__ res; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  _FW_UNDER_SURVEY ; 
 int /*<<< orphan*/  clr_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_free_cmd_obj (struct cmd_obj*) ; 

void r8712_survey_cmd_callback(struct _adapter *padapter, struct cmd_obj *pcmd)
{
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (pcmd->res != H2C_SUCCESS)
		clr_fwstate(pmlmepriv, _FW_UNDER_SURVEY);
	r8712_free_cmd_obj(pcmd);
}