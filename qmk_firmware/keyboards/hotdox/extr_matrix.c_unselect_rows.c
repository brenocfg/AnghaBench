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
 int DDRF ; 
 int PF0 ; 
 int PF1 ; 
 int PF4 ; 
 int PF5 ; 
 int PF6 ; 
 int PF7 ; 
 int PORTF ; 
 int /*<<< orphan*/  left_unselect_rows () ; 

__attribute__((used)) static void unselect_rows(void)
{
  // Pro Micro
  DDRF  &= ~(1<<PF7 | 1<< PF6 | 1<<PF5 | 1<<PF4 | 1<<PF1 | 1<<PF0);
  PORTF &= ~(1<<PF7 | 1<< PF6 | 1<<PF5 | 1<<PF4 | 1<<PF1 | 1<<PF0);

  left_unselect_rows();
}