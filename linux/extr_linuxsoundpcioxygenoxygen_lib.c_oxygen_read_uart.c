#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* uart_input ) (struct oxygen*) ;} ;
struct oxygen {scalar_t__ uart_input_count; TYPE_1__ model; scalar_t__* uart_input; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ MPU401_ACK ; 
 int /*<<< orphan*/  OXYGEN_MPU401 ; 
 scalar_t__ oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 scalar_t__ oxygen_uart_input_ready (struct oxygen*) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void oxygen_read_uart(struct oxygen *chip)
{
	if (unlikely(!oxygen_uart_input_ready(chip))) {
		/* no data, but read it anyway to clear the interrupt */
		oxygen_read8(chip, OXYGEN_MPU401);
		return;
	}
	do {
		u8 data = oxygen_read8(chip, OXYGEN_MPU401);
		if (data == MPU401_ACK)
			continue;
		if (chip->uart_input_count >= ARRAY_SIZE(chip->uart_input))
			chip->uart_input_count = 0;
		chip->uart_input[chip->uart_input_count++] = data;
	} while (oxygen_uart_input_ready(chip));
	if (chip->model.uart_input)
		chip->model.uart_input(chip);
}