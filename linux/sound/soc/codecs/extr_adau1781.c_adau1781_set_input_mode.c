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
struct adau {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ADAU1781_INPUT_DIFFERNTIAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int adau1781_set_input_mode(struct adau *adau, unsigned int reg,
	bool differential)
{
	unsigned int val;

	if (differential)
		val = ADAU1781_INPUT_DIFFERNTIAL;
	else
		val = 0;

	return regmap_update_bits(adau->regmap, reg,
		ADAU1781_INPUT_DIFFERNTIAL, val);
}