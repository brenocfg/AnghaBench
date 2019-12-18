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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int matrix_row_t ;

/* Variables and functions */
 int PB0 ; 
 int PB1 ; 
 int PB2 ; 
 int PB3 ; 
 int PC6 ; 
 int PD2 ; 
 int PD3 ; 
 int PINB ; 
 int PINC ; 
 int PIND ; 
 int left_read_cols () ; 

__attribute__((used)) static matrix_row_t read_cols(uint8_t row)
{
  matrix_row_t cols0 = 0x00, cols1 = 0x00;

  cols0 = left_read_cols();

  cols1 = (PINC&(1<<PC6) ? 0 : (1<<(0+7))) |
          (PIND&(1<<PD3) ? 0 : (1<<(1+7))) |
          (PIND&(1<<PD2) ? 0 : (1<<(2+7))) |
          (PINB&(1<<PB3) ? 0 : (1<<(3+7))) |
          (PINB&(1<<PB2) ? 0 : (1<<(4+7))) |
          (PINB&(1<<PB1) ? 0 : (1<<(5+7))) |
          (PINB&(1<<PB0) ? 0 : (1<<(6+7))) ;

  return (cols0 | cols1);
}