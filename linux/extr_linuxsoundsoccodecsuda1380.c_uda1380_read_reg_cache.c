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
typedef  unsigned int u16 ;
struct uda1380_priv {unsigned int* reg_cache; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 unsigned int UDA1380_CACHEREGNUM ; 
 unsigned int UDA1380_RESET ; 
 struct uda1380_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static inline unsigned int uda1380_read_reg_cache(struct snd_soc_component *component,
	unsigned int reg)
{
	struct uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	u16 *cache = uda1380->reg_cache;

	if (reg == UDA1380_RESET)
		return 0;
	if (reg >= UDA1380_CACHEREGNUM)
		return -1;
	return cache[reg];
}