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
 int PORTB ; 
 int PORTD ; 

void set_layer_led(int layerId) {
	PORTD |= (1<<5);
	PORTB &= ~(1<<6);
	PORTB |= (1<<0);
	switch(layerId) {
		case 0:
			PORTD &= ~(1<<5);
			break;
		case 1:
			PORTB |= (1<<6);
			break;
		case 2:
			PORTB &= ~(1<<0);
			break;
	}
}