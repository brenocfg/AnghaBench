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
struct oxygen {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void se6x_init(struct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, 0x005);

	snd_component_add(chip->card, "PCM1792A");
	snd_component_add(chip->card, "PCM1804");
}