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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98095_priv {scalar_t__ mic_jack; scalar_t__ headphone_jack; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_soc_component*) ; 
 int /*<<< orphan*/  max98095_jack_detect_disable (struct snd_soc_component*) ; 
 struct max98095_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max98095_remove(struct snd_soc_component *component)
{
	struct max98095_priv *max98095 = snd_soc_component_get_drvdata(component);
	struct i2c_client *client = to_i2c_client(component->dev);

	if (max98095->headphone_jack || max98095->mic_jack)
		max98095_jack_detect_disable(component);

	if (client->irq)
		free_irq(client->irq, component);
}