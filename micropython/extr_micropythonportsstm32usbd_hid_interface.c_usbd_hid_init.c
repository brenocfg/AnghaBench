#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usbd_hid_state_t ;
struct TYPE_2__ {size_t current_write_buffer; int /*<<< orphan*/ ** buffer; scalar_t__ last_read_len; scalar_t__ current_read_buffer; } ;
typedef  TYPE_1__ usbd_hid_itf_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

uint8_t *usbd_hid_init(usbd_hid_state_t *hid_in) {
    usbd_hid_itf_t *hid = (usbd_hid_itf_t*)hid_in;

    hid->current_read_buffer = 0;
    hid->last_read_len = 0;
    hid->current_write_buffer = 0;

    // Return the buffer to place the first USB OUT packet
    return hid->buffer[hid->current_write_buffer];
}