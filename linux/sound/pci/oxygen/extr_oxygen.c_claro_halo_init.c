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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CLARO_DIG_COAX ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  ak4396_init (struct oxygen*) ; 
 int /*<<< orphan*/  ak5385_init (struct oxygen*) ; 
 int /*<<< orphan*/  claro_enable_hp (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void claro_halo_init(struct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_CLARO_DIG_COAX);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CLARO_DIG_COAX);
	ak4396_init(chip);
	ak5385_init(chip);
	claro_enable_hp(chip);
}