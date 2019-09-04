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
struct tb_pci_tunnel {TYPE_1__* path_to_down; TYPE_1__* path_to_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  activated; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ tb_path_is_invalid (TYPE_1__*) ; 

bool tb_pci_is_invalid(struct tb_pci_tunnel *tunnel)
{
	WARN_ON(!tunnel->path_to_up->activated);
	WARN_ON(!tunnel->path_to_down->activated);

	return tb_path_is_invalid(tunnel->path_to_up)
	       || tb_path_is_invalid(tunnel->path_to_down);
}