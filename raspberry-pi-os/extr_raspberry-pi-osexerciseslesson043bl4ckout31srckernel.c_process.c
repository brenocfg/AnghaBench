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

/* Variables and functions */
 int /*<<< orphan*/  delay (int) ; 
 unsigned int get_fpsimd_reg0 () ; 
 unsigned int get_fpsimd_reg2 () ; 
 unsigned int get_fpsimd_reg31 () ; 
 int /*<<< orphan*/  set_fpsimd_reg0 (int) ; 
 int /*<<< orphan*/  set_fpsimd_reg2 (int) ; 
 int /*<<< orphan*/  set_fpsimd_reg31 (int) ; 
 int /*<<< orphan*/  uart_send (unsigned int) ; 

void process(char *array)
{
	if(array[0] == '1') {
		set_fpsimd_reg0(1);
		set_fpsimd_reg2(2);
		set_fpsimd_reg31(3);
	} else {
		set_fpsimd_reg0(5);
		set_fpsimd_reg2(6);
		set_fpsimd_reg31(7);
	}

	while (1) {
		for (int i = 0; i < 5; i++){
			unsigned int a = get_fpsimd_reg0();
			unsigned int b = get_fpsimd_reg2();
			unsigned int c = get_fpsimd_reg31();
			uart_send(a + '0');
			delay(100000);
			uart_send(b + '0');
			delay(100000);
			uart_send(c + '0');
			delay(100000);
		}
	}
}