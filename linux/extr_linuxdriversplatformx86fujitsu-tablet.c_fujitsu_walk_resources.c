#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  address_length; int /*<<< orphan*/  minimum; } ;
struct TYPE_5__ {int /*<<< orphan*/ * interrupts; } ;
struct TYPE_6__ {TYPE_3__ io; TYPE_1__ irq; } ;
struct acpi_resource {int type; TYPE_2__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  io_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_length; } ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_END_TAG 130 
#define  ACPI_RESOURCE_TYPE_IO 129 
#define  ACPI_RESOURCE_TYPE_IRQ 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_4__ fujitsu ; 

__attribute__((used)) static acpi_status fujitsu_walk_resources(struct acpi_resource *res, void *data)
{
	switch (res->type) {
	case ACPI_RESOURCE_TYPE_IRQ:
		fujitsu.irq = res->data.irq.interrupts[0];
		return AE_OK;

	case ACPI_RESOURCE_TYPE_IO:
		fujitsu.io_base = res->data.io.minimum;
		fujitsu.io_length = res->data.io.address_length;
		return AE_OK;

	case ACPI_RESOURCE_TYPE_END_TAG:
		if (fujitsu.irq && fujitsu.io_base)
			return AE_OK;
		else
			return AE_NOT_FOUND;

	default:
		return AE_ERROR;
	}
}