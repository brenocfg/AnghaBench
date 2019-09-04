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
struct status_attr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_status_attr (int) ; 
 int /*<<< orphan*/ * status_attrs ; 
 int vhci_num_controllers ; 

__attribute__((used)) static int init_status_attrs(void)
{
	int id;

	status_attrs = kcalloc(vhci_num_controllers, sizeof(struct status_attr),
			       GFP_KERNEL);
	if (status_attrs == NULL)
		return -ENOMEM;

	for (id = 0; id < vhci_num_controllers; id++)
		set_status_attr(id);

	return 0;
}