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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 size_t MAX_OCT ; 
 size_t RGBLED_NUM ; 
 int /*<<< orphan*/ * led ; 
 int /*<<< orphan*/ * oct_hues ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  sethsv (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ *) ; 

void clueboard_set_midi_led(uint8_t base_oct, uint8_t val)
{
  uint8_t sat = 255;

  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    sethsv(oct_hues[base_oct], sat, val, (LED_TYPE *)&led[i]);
  }

  uint8_t next_oct = base_oct < MAX_OCT ? base_oct + 1 : base_oct;

  uint16_t next_hue = base_oct < MAX_OCT ? oct_hues[next_oct] : 0;
  uint8_t next_val = base_oct < MAX_OCT ? val : 0;
  uint8_t next_sat = base_oct < MAX_OCT ? sat : 0;


  for (uint8_t i = 0; i < 3; i++) {
    sethsv(next_hue, next_sat, next_val, (LED_TYPE *)&led[i]);
  }

  for (uint8_t i = 11; i < 14; i++) {
    sethsv(next_hue, next_sat, next_val, (LED_TYPE *)&led[i]);
  }

  rgblight_set();
}