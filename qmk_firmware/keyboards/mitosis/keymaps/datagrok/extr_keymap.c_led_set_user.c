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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PORTD ; 
 int /*<<< orphan*/  PORTF ; 
 int default_layer_state ; 
 int layer_state ; 
 int /*<<< orphan*/  setbits (int /*<<< orphan*/ ,int,int) ; 

void led_set_user(uint8_t usb_leds) {
  // A simple (but technically inaccurate) model of the momentary layer state:
  // Red layer active -> indicator = red
  // Blue layer active -> indicator = blue
  // Purple layer active -> indicator = purple
  // the Pro Micro tx LED displays Num Lock status.
  //
  // Workman layout active -> indicator = green
  // Workman red layer -> indicator = yellow (red + green)
  // Workman blue layer -> indicator = cyan (blue + green)
  // Workman purple layer -> indicator = white (red + blue + green)

  // Bit #            7     6     5     4     3     2     1     0
  // layer_state: [     | _xF | _xN | _xS | _xW | _xD | _xC | _xQ ]
  // usb_led      [     |     |     |kana |cmps |scrl |caps | num ]
  // PORTB:       [  NC |  10 |   9 |   8 |  14 |  16 |  15 |rxled]
  // PORTC:       [  NC |   5 |     |     |     |     |     |     ]
  // PORTD:       [   6 |  NC |txled|   4 | tx* | rx* | grn | p29 ]
  // PORTE:       [     |   7 |     |     |     |     |     |     ]
  // PORTF:       [  a0 |  a1 | red | blu |     |     |  NC |  NC ]
  //
  // PD0 is connected to the pairing switch and p29 on the wireless module.
  // PF0,PF1,PB7,PC7,PD6 are not broken out by the pro micro board. I don't understand why.
  // PB1-PB6,PD4,PD5,PD6,PF6,PF7 are not connected to the Mitosis receiver
  // board. Each may be connected to an LED by way of a resistor (4.7k to
  // match the others) for a total of 14 additional indicators.

  uint32_t portf_bits = \
    ((layer_state|default_layer_state)&0b01100000)>>1 | \
    ((layer_state|default_layer_state)&0b00010000)<<1 | \
    ((layer_state|default_layer_state)&0b01000000)>>2;
  uint32_t portd_bits = \
    (usb_leds&0b1)<<5 | \
    ((layer_state|default_layer_state)&0b1000)>>2;
  // negated because for ports 0=LED on.
  setbits(PORTF, ~portf_bits, 0b00110000);
  setbits(PORTD, ~portd_bits, 0b00100010);
}