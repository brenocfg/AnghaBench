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
 int READ_PERI_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SLC_BRIDGE_CONF ; 

void _X_slc_set_host_io_max_window(void) {
  SET_PERI_REG(SLC_BRIDGE_CONF, (READ_PERI_REG(SLC_BRIDGE_CONF) & 0xfffff0c0) | 0x720);
}