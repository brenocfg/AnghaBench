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

/* Variables and functions */
 int DDRF ; 
 int PF0 ; 
 int PF1 ; 
 int PF4 ; 
 int PF5 ; 
 int PF6 ; 
 int PF7 ; 
 int PORTF ; 
 int /*<<< orphan*/  left_select_row (int) ; 

__attribute__((used)) static void select_row(uint8_t row)
{
  // Pro Micro
  switch (row) {
  case 5:
    DDRF  |=  (1<<PF0);
    PORTF &= ~(1<<PF0);
    break;
  case 4:
    DDRF  |=  (1<<PF1);
    PORTF &= ~(1<<PF1);
    break;
  case 3:
    DDRF  |=  (1<<PF4);
    PORTF &= ~(1<<PF4);
    break;
  case 2:
    DDRF  |=  (1<<PF5);
    PORTF &= ~(1<<PF5);
    break;
  case 1:
    DDRF  |=  (1<<PF6);
    PORTF &= ~(1<<PF6);
    break;
  case 0:
    DDRF  |=  (1<<PF7);
    PORTF &= ~(1<<PF7);
    break;
  }

  left_select_row(row);
}