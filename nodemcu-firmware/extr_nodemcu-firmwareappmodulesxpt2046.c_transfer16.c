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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 void* platform_spi_send_recv (int,int,void*) ; 

__attribute__((used)) static uint16_t transfer16(uint16_t _data) {
  union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } t;
  t.val = _data;
  t.msb = platform_spi_send_recv(1, 8, t.msb);
  t.lsb = platform_spi_send_recv(1, 8, t.lsb);
  return t.val;
}