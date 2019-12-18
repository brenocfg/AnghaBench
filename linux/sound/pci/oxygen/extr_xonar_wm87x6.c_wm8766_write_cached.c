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
struct xonar_wm87x6 {unsigned int* wm8766_regs; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  wm8766_write (struct oxygen*,unsigned int,unsigned int) ; 

__attribute__((used)) static void wm8766_write_cached(struct oxygen *chip,
				unsigned int reg, unsigned int value)
{
	struct xonar_wm87x6 *data = chip->model_data;

	if (reg >= ARRAY_SIZE(data->wm8766_regs) ||
	    value != data->wm8766_regs[reg])
		wm8766_write(chip, reg, value);
}