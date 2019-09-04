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
struct resource {int dummy; } ;
struct pci_dev_resource {int /*<<< orphan*/  min_align; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 struct pci_dev_resource* res_to_dev_res (struct list_head*,struct resource*) ; 

__attribute__((used)) static resource_size_t get_res_add_align(struct list_head *head,
					 struct resource *res)
{
	struct pci_dev_resource *dev_res;

	dev_res = res_to_dev_res(head, res);
	return dev_res ? dev_res->min_align : 0;
}