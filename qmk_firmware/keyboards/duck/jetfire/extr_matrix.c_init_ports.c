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
 int DDRC ; 
 int DDRD ; 
 int DDRE ; 
 int DDRF ; 

__attribute__((used)) static void init_ports(void)
{
    // Rows are inputs (inputs are 0)
    DDRD  &= 0b11010000;
    DDRB  &= 0b01111111;
    DDRE  &= 0b11111011;

    // Columns are outputs (outputs are high)
    DDRF  |= 0b00000011;
    DDRC  |= 0b11000000;
    DDRB  |= 0b01110001;
    DDRD  |= 0b10000000;
}