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
struct mlme_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  fw_state; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void clr_fwstate(struct mlme_priv *pmlmepriv, sint state)
{
	unsigned long irqL;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if (check_fwstate(pmlmepriv, state))
		pmlmepriv->fw_state ^= state;
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
}