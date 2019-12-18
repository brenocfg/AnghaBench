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
struct madera_priv {struct madera* madera; } ;
struct madera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_IRQ_SPK_OVERHEAT ; 
 int /*<<< orphan*/  MADERA_IRQ_SPK_OVERHEAT_WARN ; 
 int /*<<< orphan*/  madera_free_irq (struct madera*,int /*<<< orphan*/ ,struct madera*) ; 

int madera_free_overheat(struct madera_priv *priv)
{
	struct madera *madera = priv->madera;

	madera_free_irq(madera, MADERA_IRQ_SPK_OVERHEAT_WARN, madera);
	madera_free_irq(madera, MADERA_IRQ_SPK_OVERHEAT, madera);

	return 0;
}