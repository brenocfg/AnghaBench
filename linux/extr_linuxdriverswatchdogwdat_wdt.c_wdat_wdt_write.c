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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wdat_wdt {TYPE_1__* pdev; } ;
struct acpi_generic_address {int access_width; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {struct acpi_generic_address register_region; } ;
struct wdat_instruction {int /*<<< orphan*/  reg; TYPE_2__ entry; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdat_wdt_write(struct wdat_wdt *wdat,
	const struct wdat_instruction *instr, u32 value)
{
	const struct acpi_generic_address *gas = &instr->entry.register_region;

	switch (gas->access_width) {
	case 1:
		iowrite8((u8)value, instr->reg);
		break;
	case 2:
		iowrite16((u16)value, instr->reg);
		break;
	case 3:
		iowrite32(value, instr->reg);
		break;
	default:
		return -EINVAL;
	}

	dev_dbg(&wdat->pdev->dev, "Wrote %#x to 0x%08llx\n", value,
		gas->address);

	return 0;
}