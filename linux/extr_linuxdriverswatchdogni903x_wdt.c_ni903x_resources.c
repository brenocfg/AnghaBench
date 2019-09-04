#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ni903x_wdt {int /*<<< orphan*/  dev; int /*<<< orphan*/  io_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  address_length; int /*<<< orphan*/  minimum; } ;
struct TYPE_4__ {TYPE_1__ io; } ;
struct acpi_resource {int type; TYPE_2__ data; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
#define  ACPI_RESOURCE_TYPE_END_TAG 129 
#define  ACPI_RESOURCE_TYPE_IO 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  NIWD_IO_SIZE ; 
 int /*<<< orphan*/  NIWD_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status ni903x_resources(struct acpi_resource *res, void *data)
{
	struct ni903x_wdt *wdt = data;
	u16 io_size;

	switch (res->type) {
	case ACPI_RESOURCE_TYPE_IO:
		if (wdt->io_base != 0) {
			dev_err(wdt->dev, "too many IO resources\n");
			return AE_ERROR;
		}

		wdt->io_base = res->data.io.minimum;
		io_size = res->data.io.address_length;

		if (io_size < NIWD_IO_SIZE) {
			dev_err(wdt->dev, "memory region too small\n");
			return AE_ERROR;
		}

		if (!devm_request_region(wdt->dev, wdt->io_base, io_size,
					 NIWD_NAME)) {
			dev_err(wdt->dev, "failed to get memory region\n");
			return AE_ERROR;
		}

		return AE_OK;

	case ACPI_RESOURCE_TYPE_END_TAG:
	default:
		/* Ignore unsupported resources, e.g. IRQ */
		return AE_OK;
	}
}