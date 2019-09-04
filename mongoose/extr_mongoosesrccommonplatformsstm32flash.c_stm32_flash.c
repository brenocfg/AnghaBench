#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_14__ {scalar_t__ flash_base; scalar_t__ flash_size; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int /*<<< orphan*/  serial ;

/* Variables and functions */
 scalar_t__ FLASH_ADDRESS ; 
 scalar_t__ STLINK_DEV_DEBUG_MODE ; 
 scalar_t__ STLINK_DEV_DFU_MODE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stlink_close (TYPE_1__*) ; 
 scalar_t__ stlink_current_mode (TYPE_1__*) ; 
 scalar_t__ stlink_enter_swd_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  stlink_exit_debug_mode (TYPE_1__*) ; 
 scalar_t__ stlink_exit_dfu_mode (TYPE_1__*) ; 
 scalar_t__ stlink_force_debug (TYPE_1__*) ; 
 int /*<<< orphan*/  stlink_fwrite_finalize (TYPE_1__*,scalar_t__) ; 
 scalar_t__ stlink_jtag_reset (TYPE_1__*,int) ; 
 TYPE_1__* stlink_open_usb (int,char*) ; 
 scalar_t__ stlink_reset (TYPE_1__*) ; 
 scalar_t__ stlink_status (TYPE_1__*) ; 
 int stlink_write_flash (TYPE_1__*,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

int stm32_flash(const char *device_name, void *data, int len) {
  stlink_t *sl = NULL;
  int err = -1;
  uint8_t serial[16];

  int j = (int) strlen(device_name);
  int length = j / 2;  // the length of the destination-array
  if (j % 2 != 0) return -1;

  for (size_t k = 0; j >= 0 && k < sizeof(serial); ++k, j -= 2) {
    char buffer[3] = {0};
    memcpy(buffer, device_name + j, 2);
    serial[length - k] = (uint8_t) strtol(buffer, NULL, 16);
  }

  sl = stlink_open_usb(1, (char *) serial);

  if (sl == NULL) return -1;

  if (stlink_current_mode(sl) == STLINK_DEV_DFU_MODE) {
    if (stlink_exit_dfu_mode(sl)) {
      printf("Failed to exit DFU mode\n");
      goto on_error;
    }
  }

  if (stlink_current_mode(sl) != STLINK_DEV_DEBUG_MODE) {
    if (stlink_enter_swd_mode(sl)) {
      printf("Failed to enter SWD mode\n");
      goto on_error;
    }
  }

  if (stlink_jtag_reset(sl, 2)) {
    printf("Failed to reset JTAG\n");
    goto on_error;
  }

  if (stlink_reset(sl)) {
    printf("Failed to reset device\n");
    goto on_error;
  }

  // Core must be halted to use RAM based flashloaders
  if (stlink_force_debug(sl)) {
    printf("Failed to halt the core\n");
    goto on_error;
  }

  if (stlink_status(sl)) {
    printf("Failed to get Core's status\n");
    goto on_error;
  }

  size_t size = 0;

  if ((FLASH_ADDRESS > sl->flash_base + sl->flash_size)) {
    printf("Unknown memory region\n");
    goto on_error;
  }

  err = stlink_write_flash(sl, FLASH_ADDRESS, (uint8_t *) data, len, 0);
  stlink_fwrite_finalize(sl, FLASH_ADDRESS);

  if (err == -1) {
    printf("stlink_fwrite_flash() == -1\n");
    goto on_error;
  }

  stlink_jtag_reset(sl, 2);
  stlink_reset(sl);

  err = 0;

on_error:
  stlink_exit_debug_mode(sl);
  stlink_close(sl);

  return err;
}