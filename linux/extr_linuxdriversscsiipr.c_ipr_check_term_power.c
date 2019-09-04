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
struct ipr_mode_pages {int dummy; } ;
struct ipr_mode_page28 {int entry_length; int num_entries; struct ipr_dev_bus_entry* bus; } ;
struct ipr_ioa_cfg {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;
struct ipr_dev_bus_entry {int flags; TYPE_2__ res_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IPR_SCSI_ATTR_NO_TERM_PWR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct ipr_mode_page28* ipr_get_mode_page (struct ipr_mode_pages*,int,int) ; 

__attribute__((used)) static void ipr_check_term_power(struct ipr_ioa_cfg *ioa_cfg,
				 struct ipr_mode_pages *mode_pages)
{
	int i;
	int entry_length;
	struct ipr_dev_bus_entry *bus;
	struct ipr_mode_page28 *mode_page;

	mode_page = ipr_get_mode_page(mode_pages, 0x28,
				      sizeof(struct ipr_mode_page28));

	entry_length = mode_page->entry_length;

	bus = mode_page->bus;

	for (i = 0; i < mode_page->num_entries; i++) {
		if (bus->flags & IPR_SCSI_ATTR_NO_TERM_PWR) {
			dev_err(&ioa_cfg->pdev->dev,
				"Term power is absent on scsi bus %d\n",
				bus->res_addr.bus);
		}

		bus = (struct ipr_dev_bus_entry *)((char *)bus + entry_length);
	}
}