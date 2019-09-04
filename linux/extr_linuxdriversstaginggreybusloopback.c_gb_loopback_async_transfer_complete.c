#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct gb_operation {int /*<<< orphan*/  id; TYPE_2__* response; TYPE_1__* request; } ;
struct gb_loopback_transfer_response {int /*<<< orphan*/  reserved1; int /*<<< orphan*/  reserved0; int /*<<< orphan*/  data; } ;
struct gb_loopback_transfer_request {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct gb_loopback_async_operation {struct gb_operation* operation; struct gb_loopback* gb; } ;
struct gb_loopback {void* gbphy_latency_ts; void* apbridge_latency_ts; TYPE_4__* connection; } ;
struct TYPE_8__ {TYPE_3__* bundle; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct gb_loopback_transfer_response* payload; } ;
struct TYPE_5__ {struct gb_loopback_transfer_request* payload; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int gb_loopback_async_transfer_complete(
				struct gb_loopback_async_operation *op_async)
{
	struct gb_loopback *gb;
	struct gb_operation *operation;
	struct gb_loopback_transfer_request *request;
	struct gb_loopback_transfer_response *response;
	size_t len;
	int retval = 0;

	gb = op_async->gb;
	operation = op_async->operation;
	request = operation->request->payload;
	response = operation->response->payload;
	len = le32_to_cpu(request->len);

	if (memcmp(request->data, response->data, len)) {
		dev_err(&gb->connection->bundle->dev,
			"Loopback Data doesn't match operation id %d\n",
			operation->id);
		retval = -EREMOTEIO;
	} else {
		gb->apbridge_latency_ts =
			(u32)__le32_to_cpu(response->reserved0);
		gb->gbphy_latency_ts =
			(u32)__le32_to_cpu(response->reserved1);
	}

	return retval;
}