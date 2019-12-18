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
typedef  scalar_t__ uint32_t ;
typedef  unsigned int uint16_t ;

/* Variables and functions */
 scalar_t__ USBx_DFIFO (int /*<<< orphan*/ ) ; 

void *USB_ReadPacket(void *dest, uint16_t len) {
  uint32_t *dest_copy = (uint32_t *)dest;
  uint32_t count32b = (len + 3U) / 4U;

  for (uint32_t i = 0; i < count32b; i++) {
    *dest_copy = USBx_DFIFO(0);
    dest_copy++;
  }
  return ((void *)dest_copy);
}