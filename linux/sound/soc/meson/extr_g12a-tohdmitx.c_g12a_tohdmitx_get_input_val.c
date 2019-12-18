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

/* Variables and functions */
 int /*<<< orphan*/  TOHDMITX_CTRL0 ; 
 unsigned int __ffs (unsigned int) ; 
 int /*<<< orphan*/  snd_soc_component_read (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int g12a_tohdmitx_get_input_val(struct snd_soc_component *component,
				       unsigned int mask)
{
	unsigned int val;

	snd_soc_component_read(component, TOHDMITX_CTRL0, &val);
	return (val & mask) >> __ffs(mask);
}