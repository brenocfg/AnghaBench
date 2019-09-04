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
typedef  void* u32 ;
struct gb_loopback_transfer_response {int /*<<< orphan*/  reserved1; int /*<<< orphan*/  reserved0; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct gb_loopback_transfer_request {int /*<<< orphan*/  reserved1; int /*<<< orphan*/  reserved0; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct gb_loopback {void* gbphy_latency_ts; void* apbridge_latency_ts; TYPE_2__* connection; } ;
struct TYPE_4__ {TYPE_1__* bundle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  GB_LOOPBACK_TYPE_TRANSFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gb_loopback_operation_sync (struct gb_loopback*,int /*<<< orphan*/ ,struct gb_loopback_transfer_response*,void*,struct gb_loopback_transfer_response*,void*) ; 
 int /*<<< orphan*/  kfree (struct gb_loopback_transfer_response*) ; 
 struct gb_loopback_transfer_response* kmalloc (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static int gb_loopback_sync_transfer(struct gb_loopback *gb, u32 len)
{
	struct gb_loopback_transfer_request *request;
	struct gb_loopback_transfer_response *response;
	int retval;

	gb->apbridge_latency_ts = 0;
	gb->gbphy_latency_ts = 0;

	request = kmalloc(len + sizeof(*request), GFP_KERNEL);
	if (!request)
		return -ENOMEM;
	response = kmalloc(len + sizeof(*response), GFP_KERNEL);
	if (!response) {
		kfree(request);
		return -ENOMEM;
	}

	memset(request->data, 0x5A, len);

	request->len = cpu_to_le32(len);
	retval = gb_loopback_operation_sync(gb, GB_LOOPBACK_TYPE_TRANSFER,
					    request, len + sizeof(*request),
					    response, len + sizeof(*response));
	if (retval)
		goto gb_error;

	if (memcmp(request->data, response->data, len)) {
		dev_err(&gb->connection->bundle->dev,
			"Loopback Data doesn't match\n");
		retval = -EREMOTEIO;
	}
	gb->apbridge_latency_ts = (u32)__le32_to_cpu(response->reserved0);
	gb->gbphy_latency_ts = (u32)__le32_to_cpu(response->reserved1);

gb_error:
	kfree(request);
	kfree(response);

	return retval;
}