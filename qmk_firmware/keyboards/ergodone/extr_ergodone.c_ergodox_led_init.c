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
 int DDRD ; 
 int PB0 ; 
 int PB3 ; 
 int PB5 ; 
 int PB6 ; 
 int PORTB ; 
 int PORTD ; 

void ergodox_led_init(void)
 {
     DDRB  |=  (1<<PB5 | 1<<PB6 | 1<<PB3);
     PORTB &= ~(1<<PB5 | 1<<PB6 | 1<<PB3);
     DDRB  |=  (1<<PB0);
     PORTB |=  (1<<PB0);
     DDRD  |=  (1<<PB5);
     PORTD |=  (1<<PB5);
}