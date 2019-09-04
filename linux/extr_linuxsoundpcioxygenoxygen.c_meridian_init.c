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
 int /*<<< orphan*/  GPIO_MERIDIAN_DIG_BOARD ; 
 int /*<<< orphan*/  GPIO_MERIDIAN_DIG_MASK ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  ak4396_init (struct oxygen*) ; 
 int /*<<< orphan*/  ak5385_init (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write16_masked (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meridian_init(struct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_MERIDIAN_DIG_MASK);
	oxygen_write16_masked(chip, OXYGEN_GPIO_DATA,
			      GPIO_MERIDIAN_DIG_BOARD, GPIO_MERIDIAN_DIG_MASK);
	ak4396_init(chip);
	ak5385_init(chip);
}