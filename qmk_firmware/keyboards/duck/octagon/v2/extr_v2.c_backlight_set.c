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
 int BACKLIGHT_ALPHA ; 
 int BACKLIGHT_EXTRA ; 
 int BACKLIGHT_FROW ; 
 int BACKLIGHT_MODNUM ; 
 int BACKLIGHT_RGB ; 
 int PORTB ; 
 int PORTE ; 
 int /*<<< orphan*/  backlight_toggle_rgb (int) ; 

void backlight_set(uint8_t level) {
  level & BACKLIGHT_ALPHA ? (PORTB |= 0b00000010) : (PORTB &= ~0b00000010);
  level & BACKLIGHT_EXTRA ? (PORTB |= 0b00000100) : (PORTB &= ~0b00000100);
  level & BACKLIGHT_MODNUM ? (PORTB |= 0b00001000) : (PORTB &= ~0b00001000);
  level & BACKLIGHT_FROW ? (PORTE |= 0b01000000) : (PORTE &= ~0b01000000);
  level & BACKLIGHT_RGB ? backlight_toggle_rgb(true) : backlight_toggle_rgb(false);
}