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
typedef  int uint8_t ;
typedef  int matrix_row_t ;

/* Variables and functions */
 int PINB ; 
 int PINC ; 
 int /*<<< orphan*/  _delay_us (int) ; 

__attribute__((used)) static matrix_row_t read_row(uint8_t row)
{
	_delay_us(30);  // without this wait read unstable value.

	//keypad and program buttons
	if (row == 12)
	{
		return ~(PINC | 0b00111111);
	}
	return ~PINB;
}