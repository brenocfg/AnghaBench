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
struct oxygen {struct generic_data* model_data; } ;
struct generic_data {int /*<<< orphan*/ * wm8785_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8785_R0 ; 
 int /*<<< orphan*/  WM8785_R2 ; 
 int /*<<< orphan*/  WM8785_R7 ; 
 int /*<<< orphan*/  wm8785_write (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8785_registers_init(struct oxygen *chip)
{
	struct generic_data *data = chip->model_data;

	wm8785_write(chip, WM8785_R7, 0);
	wm8785_write(chip, WM8785_R0, data->wm8785_regs[0]);
	wm8785_write(chip, WM8785_R2, data->wm8785_regs[2]);
}