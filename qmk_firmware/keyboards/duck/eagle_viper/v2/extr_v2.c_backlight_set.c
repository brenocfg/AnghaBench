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
 int /*<<< orphan*/  BACKLIGHT_ALPHAS ; 
 int /*<<< orphan*/  BACKLIGHT_MODNUM ; 
 int /*<<< orphan*/  PORTB ; 

void backlight_set(uint8_t level) {
  switch(level) {
  case 0:
    PORTB |= BACKLIGHT_ALPHAS;
    PORTB |= BACKLIGHT_MODNUM;
  break;
  case 1:
    PORTB &= ~BACKLIGHT_ALPHAS;
    PORTB |= BACKLIGHT_MODNUM;
  break;
  case 2:
    PORTB |= BACKLIGHT_ALPHAS;
    PORTB &= ~BACKLIGHT_MODNUM;
  break;
  case 3:
    PORTB &= ~BACKLIGHT_ALPHAS;
    PORTB &= ~BACKLIGHT_MODNUM;
  break;
  }
}