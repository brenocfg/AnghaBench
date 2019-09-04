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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  onewire_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 
 int owDefaultPower ; 

void onewire_write_bytes(uint8_t pin, const uint8_t *buf, uint16_t count, bool power /* = 0 */) {
  uint16_t i;
  for (i = 0 ; i < count ; i++)
    onewire_write(pin, buf[i], i < count-1 ? owDefaultPower : power);
}