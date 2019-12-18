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
struct oxygen {int* dac_volume; struct generic_data* model_data; } ;
struct generic_data {unsigned int dacs; int** ak4396_regs; } ;

/* Variables and functions */
 size_t AK4396_CONTROL_1 ; 
 size_t AK4396_CONTROL_2 ; 
 size_t AK4396_CONTROL_3 ; 
 int AK4396_DIF_24_MSB ; 
 size_t AK4396_LCH_ATT ; 
 int AK4396_PCM ; 
 size_t AK4396_RCH_ATT ; 
 int AK4396_RSTN ; 
 int /*<<< orphan*/  ak4396_write (struct oxygen*,unsigned int,size_t,int) ; 

__attribute__((used)) static void ak4396_registers_init(struct oxygen *chip)
{
	struct generic_data *data = chip->model_data;
	unsigned int i;

	for (i = 0; i < data->dacs; ++i) {
		ak4396_write(chip, i, AK4396_CONTROL_1,
			     AK4396_DIF_24_MSB | AK4396_RSTN);
		ak4396_write(chip, i, AK4396_CONTROL_2,
			     data->ak4396_regs[0][AK4396_CONTROL_2]);
		ak4396_write(chip, i, AK4396_CONTROL_3,
			     AK4396_PCM);
		ak4396_write(chip, i, AK4396_LCH_ATT,
			     chip->dac_volume[i * 2]);
		ak4396_write(chip, i, AK4396_RCH_ATT,
			     chip->dac_volume[i * 2 + 1]);
	}
}