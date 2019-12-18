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
 int /*<<< orphan*/  TWL6040_REG_EARCTL ; 
 int /*<<< orphan*/  TWL6040_REG_HFLGAIN ; 
 int /*<<< orphan*/  TWL6040_REG_HFOTRIM ; 
 int /*<<< orphan*/  TWL6040_REG_HFRGAIN ; 
 int /*<<< orphan*/  TWL6040_REG_HSGAIN ; 
 int /*<<< orphan*/  TWL6040_REG_HSOTRIM ; 
 int /*<<< orphan*/  TWL6040_REG_LINEGAIN ; 
 int /*<<< orphan*/  TWL6040_REG_MICLCTL ; 
 int /*<<< orphan*/  TWL6040_REG_MICRCTL ; 
 int /*<<< orphan*/  TWL6040_REG_TRIM1 ; 
 int /*<<< orphan*/  TWL6040_REG_TRIM2 ; 
 int /*<<< orphan*/  TWL6040_REG_TRIM3 ; 
 int /*<<< orphan*/  twl6040_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void twl6040_init_chip(struct snd_soc_component *component)
{
	twl6040_read(component, TWL6040_REG_TRIM1);
	twl6040_read(component, TWL6040_REG_TRIM2);
	twl6040_read(component, TWL6040_REG_TRIM3);
	twl6040_read(component, TWL6040_REG_HSOTRIM);
	twl6040_read(component, TWL6040_REG_HFOTRIM);

	/* Change chip defaults */
	/* No imput selected for microphone amplifiers */
	twl6040_write(component, TWL6040_REG_MICLCTL, 0x18);
	twl6040_write(component, TWL6040_REG_MICRCTL, 0x18);

	/*
	 * We need to lower the default gain values, so the ramp code
	 * can work correctly for the first playback.
	 * This reduces the pop noise heard at the first playback.
	 */
	twl6040_write(component, TWL6040_REG_HSGAIN, 0xff);
	twl6040_write(component, TWL6040_REG_EARCTL, 0x1e);
	twl6040_write(component, TWL6040_REG_HFLGAIN, 0x1d);
	twl6040_write(component, TWL6040_REG_HFRGAIN, 0x1d);
	twl6040_write(component, TWL6040_REG_LINEGAIN, 0);
}