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
typedef  int matrix_row_t ;

/* Variables and functions */
 int PINB ; 
 int PINC ; 

__attribute__((used)) static matrix_row_t read_cols(void)
{
  return
    (PINB&(1<<5) ? 0 : ((matrix_row_t)1<<0)) |
    (PINC&(1<<7) ? 0 : ((matrix_row_t)1<<1)) |
    (PINB&(1<<4) ? 0 : ((matrix_row_t)1<<2)) |
    (PINB&(1<<6) ? 0 : ((matrix_row_t)1<<3)) |
    (PINB&(1<<1) ? 0 : ((matrix_row_t)1<<4)) |
    (PINB&(1<<2) ? 0 : ((matrix_row_t)1<<5)) |
    (PINB&(1<<3) ? 0 : ((matrix_row_t)1<<6)) |
    (PINB&(1<<0) ? 0 : ((matrix_row_t)1<<7));
}