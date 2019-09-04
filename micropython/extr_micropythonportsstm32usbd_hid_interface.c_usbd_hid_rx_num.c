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
struct TYPE_3__ {scalar_t__ current_read_buffer; scalar_t__ current_write_buffer; } ;
typedef  TYPE_1__ usbd_hid_itf_t ;

/* Variables and functions */

int usbd_hid_rx_num(usbd_hid_itf_t *hid) {
    return hid->current_read_buffer != hid->current_write_buffer;
}