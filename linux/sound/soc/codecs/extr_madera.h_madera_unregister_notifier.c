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
struct notifier_block {int dummy; } ;
struct madera_priv {struct madera* madera; } ;
struct madera {int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int blocking_notifier_chain_unregister (int /*<<< orphan*/ *,struct notifier_block*) ; 
 struct madera_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static inline int
madera_unregister_notifier(struct snd_soc_component *component,
			   struct notifier_block *nb)
{
	struct madera_priv *priv = snd_soc_component_get_drvdata(component);
	struct madera *madera = priv->madera;

	return blocking_notifier_chain_unregister(&madera->notifier, nb);
}