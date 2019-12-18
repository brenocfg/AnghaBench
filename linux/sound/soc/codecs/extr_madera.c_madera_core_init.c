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
struct madera_priv {TYPE_1__* madera; int /*<<< orphan*/  rate_lock; } ;
struct TYPE_2__ {int* out_clamp; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int MADERA_MAX_HP_OUTPUT ; 
 int MADERA_NUM_MIXER_INPUTS ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * madera_mixer_texts ; 
 int /*<<< orphan*/ * madera_mixer_values ; 
 int /*<<< orphan*/  madera_prop_get_pdata (struct madera_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int madera_core_init(struct madera_priv *priv)
{
	int i;

	/* trap undersized array initializers */
	BUILD_BUG_ON(!madera_mixer_texts[MADERA_NUM_MIXER_INPUTS - 1]);
	BUILD_BUG_ON(!madera_mixer_values[MADERA_NUM_MIXER_INPUTS - 1]);

	if (!dev_get_platdata(priv->madera->dev))
		madera_prop_get_pdata(priv);

	mutex_init(&priv->rate_lock);

	for (i = 0; i < MADERA_MAX_HP_OUTPUT; i++)
		priv->madera->out_clamp[i] = true;

	return 0;
}