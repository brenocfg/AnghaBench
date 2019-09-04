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
typedef  int /*<<< orphan*/  u16 ;
struct gb_control_disconnected_request {int /*<<< orphan*/  cport_id; } ;
struct gb_control {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_CONTROL_TYPE_DISCONNECTED ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_control_disconnected_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_control_disconnected_operation(struct gb_control *control, u16 cport_id)
{
	struct gb_control_disconnected_request request;

	request.cport_id = cpu_to_le16(cport_id);
	return gb_operation_sync(control->connection,
				 GB_CONTROL_TYPE_DISCONNECTED, &request,
				 sizeof(request), NULL, 0);
}