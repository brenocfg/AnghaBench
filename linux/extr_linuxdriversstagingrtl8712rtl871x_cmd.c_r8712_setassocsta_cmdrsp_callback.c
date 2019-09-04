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
struct sta_priv {int dummy; } ;
struct sta_info {int /*<<< orphan*/  mac_id; int /*<<< orphan*/  aid; } ;
struct set_assocsta_rsp {int /*<<< orphan*/  cam_id; } ;
struct set_assocsta_parm {int /*<<< orphan*/  addr; } ;
struct mlme_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  fw_state; } ;
struct cmd_obj {scalar_t__ rsp; scalar_t__ parmbuf; } ;
struct _adapter {struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_free_cmd_obj (struct cmd_obj*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_setassocsta_cmdrsp_callback(struct _adapter *padapter,
				       struct cmd_obj *pcmd)
{
	unsigned long	irqL;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct set_assocsta_parm *passocsta_parm =
				(struct set_assocsta_parm *)(pcmd->parmbuf);
	struct set_assocsta_rsp *passocsta_rsp =
				(struct set_assocsta_rsp *) (pcmd->rsp);
	struct sta_info *psta = r8712_get_stainfo(pstapriv,
						  passocsta_parm->addr);

	if (!psta)
		return;
	psta->aid = psta->mac_id = passocsta_rsp->cam_id;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if ((check_fwstate(pmlmepriv, WIFI_MP_STATE)) &&
	    (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)))
		pmlmepriv->fw_state ^= _FW_UNDER_LINKING;
	set_fwstate(pmlmepriv, _FW_LINKED);
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	r8712_free_cmd_obj(pcmd);
}