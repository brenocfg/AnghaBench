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
 int CS4362A_CPEN ; 
 int CS4362A_PDN ; 
 int /*<<< orphan*/  OXYGEN_FUNCTION ; 
 int /*<<< orphan*/  OXYGEN_FUNCTION_RESET_CODEC ; 
 int /*<<< orphan*/  cs4362a_write (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  oxygen_clear_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xonar_disable_output (struct oxygen*) ; 

__attribute__((used)) static void xonar_d1_cleanup(struct oxygen *chip)
{
	xonar_disable_output(chip);
	cs4362a_write(chip, 0x01, CS4362A_PDN | CS4362A_CPEN);
	oxygen_clear_bits8(chip, OXYGEN_FUNCTION, OXYGEN_FUNCTION_RESET_CODEC);
}