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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int _stlink_usb_write_mem8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int stlink_write_mem8(stlink_t *sl, uint32_t addr, uint16_t len) {
  if (len > 0x40) {  // !!! never ever: Writing more then 0x40 bytes gives
                     // unexpected behaviour
    fprintf(stderr, "Error: Data length > 64: +%d byte.\n", len);
    abort();
  }
  return _stlink_usb_write_mem8(sl, addr, len);
}