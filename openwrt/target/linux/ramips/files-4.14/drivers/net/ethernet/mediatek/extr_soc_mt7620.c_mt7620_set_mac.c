#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mt7620_gsw {int dummy; } ;
struct fe_priv {int /*<<< orphan*/  page_lock; TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ swpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSW_REG_SMACCR0 ; 
 int /*<<< orphan*/  GSW_REG_SMACCR1 ; 
 int /*<<< orphan*/  mtk_switch_w32 (struct mt7620_gsw*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mt7620_set_mac(struct fe_priv *priv, unsigned char *mac)
{
	struct mt7620_gsw *gsw = (struct mt7620_gsw *)priv->soc->swpriv;
	unsigned long flags;

	spin_lock_irqsave(&priv->page_lock, flags);
	mtk_switch_w32(gsw, (mac[0] << 8) | mac[1], GSW_REG_SMACCR1);
	mtk_switch_w32(gsw, (mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5],
		GSW_REG_SMACCR0);
	spin_unlock_irqrestore(&priv->page_lock, flags);
}