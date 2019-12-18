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

/* Variables and functions */

void *ets_get_esf_buf_ctlblk(void) {
    // Get literal ptr before start of esf_rx_buf_alloc func
    extern void *esf_rx_buf_alloc();
    return ((void**)esf_rx_buf_alloc)[-1];
}