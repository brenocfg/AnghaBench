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
 int DDRB ; 
 int PD3 ; 
 int PORTB ; 

__attribute__((used)) static void  unselect_cols(void)
{
  // output high(DDR:1, PORT:1) to unselect
  DDRB  |= (1 << PD3);
  PORTB |= (1 << PD3);
}