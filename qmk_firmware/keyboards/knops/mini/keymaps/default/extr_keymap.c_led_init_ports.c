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
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTE ; 

void led_init_ports() {
  // led voor switch #1
	DDRD |= (1<<7);
	PORTD &= ~(1<<7);
	
  // led voor switch #2
	DDRC |= (1<<6);
	DDRC |= (1<<7);
	PORTC &= ~(1<<6);
	PORTC &= ~(1<<7);
	
  // led voor switch #3
	DDRD |= (1<<4);
	PORTD &= ~(1<<4);
	
  // led voor switch #4
	DDRE |= (1<<6);
	PORTE &= ~(1<<6);
	
  // led voor switch #5
	DDRB |= (1<<4);
	PORTB &= ~(1<<4);
	
  // led voor switch #6
	DDRD |= (1<<6);
	PORTD &= ~(1<<6);
	
	/*
	DDRD |= (1<<7);
	PORTD |= (1<<7);
	
	DDRC |= (1<<6);
	PORTC |= (1<<6);
	
	DDRD |= (1<<4);
	PORTD |= (1<<4);
	
	DDRE |= (1<<6);
	PORTE |= (1<<6);
	
	DDRB |= (1<<4);
	PORTB |= (1<<4);
	
	DDRD |= (1<<6);
	PORTD |= (1<<6);
	// */	

	DDRD |= (1<<5);
	DDRB |= (1<<6);
	DDRB |= (1<<0);
	//led_set_layer(0);
}