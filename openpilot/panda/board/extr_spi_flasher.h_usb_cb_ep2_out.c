#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int CR; int SR; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_led ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_2__* FLASH ; 
 int FLASH_CR_PG ; 
 int FLASH_CR_PSIZE_1 ; 
 int FLASH_SR_BSY ; 
 int /*<<< orphan*/  LED_RED ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 TYPE_1__* current_board ; 
 int /*<<< orphan*/ * prog_ptr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

void usb_cb_ep2_out(void *usbdata, int len, bool hardwired) {
  UNUSED(hardwired);
  current_board->set_led(LED_RED, 0);
  for (int i = 0; i < len/4; i++) {
    // program byte 1
    FLASH->CR = FLASH_CR_PSIZE_1 | FLASH_CR_PG;

    *prog_ptr = *(uint32_t*)(usbdata+(i*4));
    while (FLASH->SR & FLASH_SR_BSY);

    //*(uint64_t*)(&spi_tx_buf[0x30+(i*4)]) = *prog_ptr;
    prog_ptr++;
  }
  current_board->set_led(LED_RED, 1);
}