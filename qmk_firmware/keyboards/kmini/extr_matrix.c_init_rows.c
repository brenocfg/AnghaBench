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
 int DDRD ; 
 int DDRE ; 
 int PORTD ; 
 int PORTE ; 

__attribute__((used)) static void init_rows(void) {
    DDRD  &= ~((1<<0)| (1<<1) | (1<<2) | (1<<3) | (1<<5)); // IN
    PORTD &= ~((1<<0)| (1<<1) | (1<<2) | (1<<3) | (1<<5)); // LO

    DDRE &= ~(1<<2); // IN
    PORTE |= (1<<2); // HI
}