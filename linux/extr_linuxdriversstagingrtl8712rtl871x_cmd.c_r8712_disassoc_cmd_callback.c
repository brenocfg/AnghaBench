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
struct mlme_priv {int /*<<< orphan*/  lock; } ;
struct cmd_obj {scalar_t__ res; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  r8712_free_cmd_obj (struct cmd_obj*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_disassoc_cmd_callback(struct _adapter *padapter,
				 struct cmd_obj *pcmd)
{
	unsigned long irqL;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (pcmd->res != H2C_SUCCESS) {
		spin_lock_irqsave(&pmlmepriv->lock, irqL);
		set_fwstate(pmlmepriv, _FW_LINKED);
		spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
		return;
	}
	r8712_free_cmd_obj(pcmd);
}