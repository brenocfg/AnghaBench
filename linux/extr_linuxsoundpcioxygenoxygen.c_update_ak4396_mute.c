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
typedef  int u8 ;
struct oxygen {scalar_t__ dac_mute; struct generic_data* model_data; } ;
struct generic_data {int** ak4396_regs; unsigned int dacs; } ;

/* Variables and functions */
 size_t AK4396_CONTROL_2 ; 
 int AK4396_SMUTE ; 
 int /*<<< orphan*/  ak4396_write_cached (struct oxygen*,unsigned int,size_t,int) ; 

__attribute__((used)) static void update_ak4396_mute(struct oxygen *chip)
{
	struct generic_data *data = chip->model_data;
	unsigned int i;
	u8 value;

	value = data->ak4396_regs[0][AK4396_CONTROL_2] & ~AK4396_SMUTE;
	if (chip->dac_mute)
		value |= AK4396_SMUTE;
	for (i = 0; i < data->dacs; ++i)
		ak4396_write_cached(chip, i, AK4396_CONTROL_2, value);
}