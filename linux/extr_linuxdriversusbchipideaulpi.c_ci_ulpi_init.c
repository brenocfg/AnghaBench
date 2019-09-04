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
struct TYPE_4__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct ci_hdrc {int /*<<< orphan*/  ulpi; int /*<<< orphan*/  dev; TYPE_2__ ulpi_ops; TYPE_1__* platdata; } ;
struct TYPE_3__ {scalar_t__ phy_mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 scalar_t__ USBPHY_INTERFACE_MODE_ULPI ; 
 int /*<<< orphan*/  ci_ulpi_read ; 
 int /*<<< orphan*/  ci_ulpi_write ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw_phymode_configure (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ulpi_register_interface (int /*<<< orphan*/ ,TYPE_2__*) ; 

int ci_ulpi_init(struct ci_hdrc *ci)
{
	if (ci->platdata->phy_mode != USBPHY_INTERFACE_MODE_ULPI)
		return 0;

	/*
	 * Set PORTSC correctly so we can read/write ULPI registers for
	 * identification purposes
	 */
	hw_phymode_configure(ci);

	ci->ulpi_ops.read = ci_ulpi_read;
	ci->ulpi_ops.write = ci_ulpi_write;
	ci->ulpi = ulpi_register_interface(ci->dev, &ci->ulpi_ops);
	if (IS_ERR(ci->ulpi))
		dev_err(ci->dev, "failed to register ULPI interface");

	return PTR_ERR_OR_ZERO(ci->ulpi);
}