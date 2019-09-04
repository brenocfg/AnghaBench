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
struct TYPE_3__ {scalar_t__ connect_state; } ;
typedef  TYPE_1__ usbd_cdc_itf_t ;

/* Variables and functions */
 scalar_t__ USBD_CDC_CONNECT_STATE_CONNECTED ; 

__attribute__((used)) static inline int usbd_cdc_is_connected(usbd_cdc_itf_t *cdc) {
    return cdc->connect_state == USBD_CDC_CONNECT_STATE_CONNECTED;
}