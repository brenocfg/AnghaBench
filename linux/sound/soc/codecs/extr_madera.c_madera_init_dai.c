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
struct madera_priv {struct madera_dai_priv* dai; } ;
struct madera_dai_priv {int /*<<< orphan*/  constraint; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_CLK_SYSCLK_1 ; 
 int /*<<< orphan*/  madera_constraint ; 

int madera_init_dai(struct madera_priv *priv, int id)
{
	struct madera_dai_priv *dai_priv = &priv->dai[id];

	dai_priv->clk = MADERA_CLK_SYSCLK_1;
	dai_priv->constraint = madera_constraint;

	return 0;
}