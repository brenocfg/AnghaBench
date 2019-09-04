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
typedef  int /*<<< orphan*/  volatile uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ ptrdiff_t ;

/* Variables and functions */

uint8_t wizchip_bus_readbyte(uint32_t AddrSel) { return * ((volatile uint8_t *)((ptrdiff_t) AddrSel)); }