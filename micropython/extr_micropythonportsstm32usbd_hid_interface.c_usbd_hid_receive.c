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
struct TYPE_2__ {int current_write_buffer; size_t last_read_len; int /*<<< orphan*/  base; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ usbd_hid_itf_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  USBD_HID_ReceivePacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBD_HID_SetNAK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBD_OK ; 

int8_t usbd_hid_receive(usbd_hid_state_t *hid_in, size_t len) {
    usbd_hid_itf_t *hid = (usbd_hid_itf_t*)hid_in;

    hid->current_write_buffer = !hid->current_write_buffer;
    hid->last_read_len = len;
    // initiate next USB packet transfer, to append to existing data in buffer
    USBD_HID_ReceivePacket(&hid->base, hid->buffer[hid->current_write_buffer]);
    // Set NAK to indicate we need to process read buffer
    USBD_HID_SetNAK(&hid->base);
    return USBD_OK;
}