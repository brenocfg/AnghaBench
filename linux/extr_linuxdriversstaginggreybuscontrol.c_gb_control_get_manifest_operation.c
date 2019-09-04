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
struct gb_interface {TYPE_1__* control; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {struct gb_connection* connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_CONTROL_TYPE_GET_MANIFEST ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 

int gb_control_get_manifest_operation(struct gb_interface *intf, void *manifest,
				      size_t size)
{
	struct gb_connection *connection = intf->control->connection;

	return gb_operation_sync(connection, GB_CONTROL_TYPE_GET_MANIFEST,
				NULL, 0, manifest, size);
}