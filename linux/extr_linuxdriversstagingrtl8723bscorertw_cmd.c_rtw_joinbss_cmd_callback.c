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
struct mlme_priv {int /*<<< orphan*/  assoc_timer; } ;
struct cmd_obj {scalar_t__ res; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ H2C_DROPPED ; 
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 

void rtw_joinbss_cmd_callback(struct adapter *padapter,  struct cmd_obj *pcmd)
{
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (pcmd->res == H2C_DROPPED) {
		/* TODO: cancel timer and do timeout handler directly... */
		/* need to make timeout handlerOS independent */
		_set_timer(&pmlmepriv->assoc_timer, 1);
	} else if (pcmd->res != H2C_SUCCESS) {
		_set_timer(&pmlmepriv->assoc_timer, 1);
	}

	rtw_free_cmd_obj(pcmd);
}