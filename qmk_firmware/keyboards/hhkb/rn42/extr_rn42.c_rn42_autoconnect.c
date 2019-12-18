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
 int PORTF ; 

void rn42_autoconnect(void)
{
    // hi to auto connect
    DDRF |= (1<<7);
    PORTF |= (1<<7);
}