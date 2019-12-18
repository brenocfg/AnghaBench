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
struct snd_soc_component {int dummy; } ;
struct arizona_priv {unsigned int dvfs_reqs; int /*<<< orphan*/  dvfs_lock; int /*<<< orphan*/  dvfs_cached; } ;

/* Variables and functions */
 int arizona_dvfs_disable (struct snd_soc_component*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int arizona_dvfs_down(struct snd_soc_component *component, unsigned int flags)
{
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	unsigned int old_reqs;
	int ret = 0;

	mutex_lock(&priv->dvfs_lock);

	old_reqs = priv->dvfs_reqs;
	priv->dvfs_reqs &= ~flags;

	if (!priv->dvfs_cached && old_reqs && !priv->dvfs_reqs)
		ret = arizona_dvfs_disable(component);

	mutex_unlock(&priv->dvfs_lock);
	return ret;
}