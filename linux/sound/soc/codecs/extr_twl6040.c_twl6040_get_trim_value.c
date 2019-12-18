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
typedef  enum twl6040_trim { ____Placeholder_twl6040_trim } twl6040_trim ;

/* Variables and functions */
 int EINVAL ; 
 int TWL6040_REG_TRIM1 ; 
 int TWL6040_TRIM_INVAL ; 
 int twl6040_read (struct snd_soc_component*,int) ; 
 scalar_t__ unlikely (int) ; 

int twl6040_get_trim_value(struct snd_soc_component *component, enum twl6040_trim trim)
{
	if (unlikely(trim >= TWL6040_TRIM_INVAL))
		return -EINVAL;

	return twl6040_read(component, TWL6040_REG_TRIM1 + trim);
}