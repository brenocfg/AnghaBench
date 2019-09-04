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
struct tlv320dac33_priv {int /*<<< orphan*/  mutex; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int dac33_write (struct snd_soc_component*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int dac33_write_locked(struct snd_soc_component *component, unsigned int reg,
			      unsigned int value)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	int ret;

	mutex_lock(&dac33->mutex);
	ret = dac33_write(component, reg, value);
	mutex_unlock(&dac33->mutex);

	return ret;
}