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
 int PB4 ; 
 int PC6 ; 
 int PD2 ; 
 int PD3 ; 
 int PD4 ; 
 int PD7 ; 
 int PE6 ; 
 int PINB ; 
 int PINC ; 
 int PIND ; 
 int PINE ; 
 int expander_read_row () ; 

__attribute__((used)) static matrix_row_t read_cols(uint8_t row)
{
  return expander_read_row() |
    (PIND&(1<<PD3) ? 0 : (1<<6)) |
    (PIND&(1<<PD2) ? 0 : (1<<5)) |
    (PIND&(1<<PD4) ? 0 : (1<<4)) |
    (PINC&(1<<PC6) ? 0 : (1<<3)) |
    (PIND&(1<<PD7) ? 0 : (1<<2)) |
    (PINE&(1<<PE6) ? 0 : (1<<1)) |
    (PINB&(1<<PB4) ? 0 : (1<<0)) ;
}