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
struct notifier_block {int (* notifier_call ) (struct notifier_block*,unsigned long,void*) ;} ;
struct arizona_priv {struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static inline int arizona_register_notifier(struct snd_soc_component *component,
					    struct notifier_block *nb,
					    int (*notify)
					    (struct notifier_block *nb,
					    unsigned long action, void *data))
{
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona *arizona = priv->arizona;

	nb->notifier_call = notify;

	return blocking_notifier_chain_register(&arizona->notifier, nb);
}