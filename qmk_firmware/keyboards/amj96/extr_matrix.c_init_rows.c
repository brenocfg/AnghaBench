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
 int PB1 ; 
 int PB2 ; 
 int PB3 ; 

__attribute__((used)) static void init_rows(void)
{
     DDRB  |= (1<<PB1 | 1<<PB2 | 1<<PB3);
}