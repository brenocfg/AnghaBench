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
 int /*<<< orphan*/  apa102_send_byte (int,int,int) ; 

__attribute__((used)) static void apa102_send_buffer(uint32_t data_pin, uint32_t clock_pin, uint32_t *buf, uint32_t nbr_frames) {
  int i;

  // Send 32-bit Start Frame that's all 0x00
  apa102_send_byte(data_pin, clock_pin, 0x00);
  apa102_send_byte(data_pin, clock_pin, 0x00);
  apa102_send_byte(data_pin, clock_pin, 0x00);
  apa102_send_byte(data_pin, clock_pin, 0x00);

  // Send 32-bit LED Frames
  for (i = 0; i < nbr_frames; i++) {
    uint8_t *byte = (uint8_t *) buf++;

    // Set the first 3 bits of that byte to 1.
    // This makes the lua interface easier to use since you
    // don't have to worry about creating invalid LED Frames.
    byte[0] |= 0xE0;
    apa102_send_byte(data_pin, clock_pin, byte[0]);
    apa102_send_byte(data_pin, clock_pin, byte[1]);
    apa102_send_byte(data_pin, clock_pin, byte[2]);
    apa102_send_byte(data_pin, clock_pin, byte[3]);
  }

  // Send 32-bit End Frames
  uint32_t required_postamble_frames = (nbr_frames + 1) / 2;
  for (i = 0; i < required_postamble_frames; i++) {
    apa102_send_byte(data_pin, clock_pin, 0xFF);
    apa102_send_byte(data_pin, clock_pin, 0xFF);
    apa102_send_byte(data_pin, clock_pin, 0xFF);
    apa102_send_byte(data_pin, clock_pin, 0xFF);
  }
}