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
struct gb_svc_intf_oops_request {int dummy; } ;
struct gb_svc {int /*<<< orphan*/  dev; } ;
struct gb_operation {TYPE_1__* request; int /*<<< orphan*/  connection; } ;
struct TYPE_2__ {int payload_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 struct gb_svc* gb_connection_get_data (int /*<<< orphan*/ ) ; 
 int gb_svc_queue_deferred_request (struct gb_operation*) ; 

__attribute__((used)) static int gb_svc_intf_oops_recv(struct gb_operation *op)
{
	struct gb_svc *svc = gb_connection_get_data(op->connection);
	struct gb_svc_intf_oops_request *request;

	if (op->request->payload_size < sizeof(*request)) {
		dev_warn(&svc->dev, "short intf-oops request received (%zu < %zu)\n",
			 op->request->payload_size, sizeof(*request));
		return -EINVAL;
	}

	return gb_svc_queue_deferred_request(op);
}