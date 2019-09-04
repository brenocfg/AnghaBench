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
typedef  int u8 ;
struct mlme_priv {int /*<<< orphan*/  lock; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_disassoc_cmd (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_assoc_resources (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_ind_disconnect (struct _adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u8 r8712_set_802_11_disassociate(struct _adapter *padapter)
{
	unsigned long irqL;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if (check_fwstate(pmlmepriv, _FW_LINKED)) {
		r8712_disassoc_cmd(padapter);
		r8712_ind_disconnect(padapter);
		r8712_free_assoc_resources(padapter);
	}
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	return true;
}