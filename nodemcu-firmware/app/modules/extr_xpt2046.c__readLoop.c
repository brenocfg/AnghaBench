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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int platform_spi_send_recv (int,int,scalar_t__) ; 

__attribute__((used)) static uint16_t _readLoop(uint8_t ctrl, uint8_t max_samples) {
  uint16_t prev = 0xffff, cur = 0xffff;
  uint8_t i = 0;
  do {
    prev = cur;
    cur = platform_spi_send_recv(1, 8 , 0);
    cur = (cur << 4) | (platform_spi_send_recv(1, 8 , ctrl) >> 4);  // 16 clocks -> 12-bits (zero-padded at end)
  } while ((prev != cur) && (++i < max_samples));
  return cur;
}