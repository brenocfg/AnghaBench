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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 scalar_t__ PAL_HIGH ; 
 scalar_t__ palReadPad (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static matrix_row_t read_cols(void){
  return ((palReadPad(GPIOA, 5)==PAL_HIGH) ? 0 : (1<<0))
    | ((palReadPad(GPIOA, 15)==PAL_HIGH) ? 0 : (1<<1))
    | ((palReadPad(GPIOA, 10)==PAL_HIGH) ? 0 : (1<<2))
    | ((palReadPad(GPIOA, 9)==PAL_HIGH) ? 0 : (1<<3))
    | ((palReadPad(GPIOA, 8)==PAL_HIGH) ? 0 : (1<<4))
    | ((palReadPad(GPIOB, 15)==PAL_HIGH) ? 0 : (1<<5))
    | ((palReadPad(GPIOB, 14)==PAL_HIGH) ? 0 : (1<<6))
    | ((palReadPad(GPIOB, 13)==PAL_HIGH) ? 0 : (1<<7))
    | ((palReadPad(GPIOB, 12)==PAL_HIGH) ? 0 : (1<<8))
    | ((palReadPad(GPIOB, 11)==PAL_HIGH) ? 0 : (1<<9))
    | ((palReadPad(GPIOB, 10)==PAL_HIGH) ? 0 : (1<<10))
    | ((palReadPad(GPIOB, 1)==PAL_HIGH) ? 0 : (1<<11))
    | ((palReadPad(GPIOB, 0)==PAL_HIGH) ? 0 : (1<<12))
    | ((palReadPad(GPIOA, 7)==PAL_HIGH) ? 0 : (1<<13))
    | ((palReadPad(GPIOA, 6)==PAL_HIGH) ? 0 : (1<<14));
}