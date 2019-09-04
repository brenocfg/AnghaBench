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
struct xenstore_domain_interface {scalar_t__ req_prod; scalar_t__ req_cons; } ;

/* Variables and functions */
 scalar_t__ XENSTORE_RING_SIZE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xb_write_list ; 
 struct xenstore_domain_interface* xen_store_interface ; 

__attribute__((used)) static int xb_data_to_write(void)
{
	struct xenstore_domain_interface *intf = xen_store_interface;

	return (intf->req_prod - intf->req_cons) != XENSTORE_RING_SIZE &&
		!list_empty(&xb_write_list);
}