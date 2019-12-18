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
 int DDRF ; 
 int PB1 ; 
 int PB2 ; 
 int PF4 ; 
 int PF5 ; 
 int PF6 ; 
 int PF7 ; 
 int PORTB ; 
 int PORTF ; 
 int /*<<< orphan*/  expander_unselect_rows () ; 

__attribute__((used)) static void unselect_rows(void)
{
  // Pro Micro
  DDRF  &= ~(1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
  PORTF &= ~(1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
  DDRB  &= ~(1<<PB1 | 1<<PB2);
  PORTB &= ~(1<<PB1 | 1<<PB2);

  // Expander
  expander_unselect_rows();
}