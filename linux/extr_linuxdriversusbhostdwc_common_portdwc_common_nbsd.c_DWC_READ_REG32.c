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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ioh; int /*<<< orphan*/  iot; } ;
typedef  TYPE_1__ dwc_ioctx_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t DWC_READ_REG32(void *io_ctx, uint32_t volatile *reg)
{
	dwc_ioctx_t *io = (dwc_ioctx_t *)io_ctx;
	bus_size_t ior = (bus_size_t)reg;

	return bus_space_read_4(io->iot, io->ioh, ior);
}