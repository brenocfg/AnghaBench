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
struct ht_priv {int ht_option; int* baddbareq_issued; scalar_t__ ampdu_enable; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_addbareq_cmd (struct _adapter*,int /*<<< orphan*/ ) ; 

void r8712_issue_addbareq_cmd(struct _adapter *padapter, int priority)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv	 *phtpriv = &pmlmepriv->htpriv;

	if ((phtpriv->ht_option == 1) && (phtpriv->ampdu_enable)) {
		if (!phtpriv->baddbareq_issued[priority]) {
			r8712_addbareq_cmd(padapter, (u8)priority);
			phtpriv->baddbareq_issued[priority] = true;
		}
	}
}