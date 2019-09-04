#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t current_read_buffer; size_t current_write_buffer; size_t last_read_len; int /*<<< orphan*/  base; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ usbd_hid_itf_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ HAL_GetTick () ; 
 scalar_t__ IRQ_STATE_DISABLED ; 
 int /*<<< orphan*/  USBD_HID_ClearNAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __WFI () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ query_irq () ; 

int usbd_hid_rx(usbd_hid_itf_t *hid, size_t len, uint8_t *buf, uint32_t timeout) {
    // Wait until we have buffer to read
    uint32_t start = HAL_GetTick();
    while (hid->current_read_buffer == hid->current_write_buffer) {
        // Wraparound of tick is taken care of by 2's complement arithmetic.
        if (HAL_GetTick() - start >= timeout) {
            // timeout
            return 0;
        }
        if (query_irq() == IRQ_STATE_DISABLED) {
            // IRQs disabled so buffer will never be filled; return immediately
            return 0;
        }
        __WFI(); // enter sleep mode, waiting for interrupt
    }

    // There is not enough space in buffer
    if (len < hid->last_read_len) {
        return 0;
    }

    // Copy bytes from device to user buffer
    int read_len = hid->last_read_len;
    memcpy(buf, hid->buffer[hid->current_read_buffer], read_len);
    hid->current_read_buffer = !hid->current_read_buffer;

    // Clear NAK to indicate we are ready to read more data
    USBD_HID_ClearNAK(&hid->base);

    // Success, return number of bytes read
    return read_len;
}