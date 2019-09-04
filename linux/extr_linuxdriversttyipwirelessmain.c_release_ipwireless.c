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
struct ipw_dev {TYPE_2__* link; scalar_t__ attr_memory; scalar_t__ common_memory; } ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_disable_device (TYPE_2__*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static void release_ipwireless(struct ipw_dev *ipw)
{
	release_region(ipw->link->resource[0]->start,
		       resource_size(ipw->link->resource[0]));
	if (ipw->common_memory) {
		release_mem_region(ipw->link->resource[2]->start,
				resource_size(ipw->link->resource[2]));
		iounmap(ipw->common_memory);
	}
	if (ipw->attr_memory) {
		release_mem_region(ipw->link->resource[3]->start,
				resource_size(ipw->link->resource[3]));
		iounmap(ipw->attr_memory);
	}
	pcmcia_disable_device(ipw->link);
}