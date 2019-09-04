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
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__* epf; } ;
struct TYPE_3__ {int /*<<< orphan*/  msix_interrupts; } ;

/* Variables and functions */
 int kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* to_pci_epf_group (struct config_item*) ; 

__attribute__((used)) static ssize_t pci_epf_msix_interrupts_store(struct config_item *item,
					     const char *page, size_t len)
{
	u16 val;
	int ret;

	ret = kstrtou16(page, 0, &val);
	if (ret)
		return ret;

	to_pci_epf_group(item)->epf->msix_interrupts = val;

	return len;
}