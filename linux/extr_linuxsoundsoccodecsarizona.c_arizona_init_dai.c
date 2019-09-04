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
struct arizona_priv {struct arizona_dai_priv* dai; } ;
struct arizona_dai_priv {int /*<<< orphan*/  constraint; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  arizona_constraint ; 

int arizona_init_dai(struct arizona_priv *priv, int id)
{
	struct arizona_dai_priv *dai_priv = &priv->dai[id];

	dai_priv->clk = ARIZONA_CLK_SYSCLK;
	dai_priv->constraint = arizona_constraint;

	return 0;
}