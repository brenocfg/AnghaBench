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
typedef  unsigned int u8 ;
struct tlv320dac33_priv {unsigned int* reg_cache; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned int DAC33_CACHEREGNUM ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static inline unsigned int dac33_read_reg_cache(struct snd_soc_component *component,
						unsigned reg)
{
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	u8 *cache = dac33->reg_cache;
	if (reg >= DAC33_CACHEREGNUM)
		return 0;

	return cache[reg];
}