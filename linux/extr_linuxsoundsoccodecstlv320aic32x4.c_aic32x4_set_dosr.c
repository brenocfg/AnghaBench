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
typedef  int u16 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_DOSRLSB ; 
 int /*<<< orphan*/  AIC32X4_DOSRMSB ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic32x4_set_dosr(struct snd_soc_component *component, u16 dosr)
{
	snd_soc_component_write(component, AIC32X4_DOSRMSB, dosr >> 8);
	snd_soc_component_write(component, AIC32X4_DOSRLSB,
		      (dosr & 0xff));

	return 0;
}