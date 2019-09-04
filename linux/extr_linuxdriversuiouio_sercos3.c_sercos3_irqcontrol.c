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
struct uio_info {struct sercos3_priv* priv; } ;
struct sercos3_priv {int /*<<< orphan*/  ier0_cache_lock; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  sercos3_disable_interrupts (struct uio_info*,struct sercos3_priv*) ; 
 int /*<<< orphan*/  sercos3_enable_interrupts (struct uio_info*,struct sercos3_priv*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sercos3_irqcontrol(struct uio_info *info, s32 irq_on)
{
	struct sercos3_priv *priv = info->priv;

	spin_lock_irq(&priv->ier0_cache_lock);
	if (irq_on)
		sercos3_enable_interrupts(info, priv);
	else
		sercos3_disable_interrupts(info, priv);
	spin_unlock_irq(&priv->ier0_cache_lock);

	return 0;
}