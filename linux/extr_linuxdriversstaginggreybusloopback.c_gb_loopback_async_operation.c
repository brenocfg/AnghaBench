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
struct gb_operation {TYPE_1__* request; } ;
struct gb_loopback_async_operation {int /*<<< orphan*/  ts; void* completion; struct gb_operation* operation; struct gb_loopback* gb; } ;
struct gb_loopback {int /*<<< orphan*/  outstanding_operations; int /*<<< orphan*/  jiffy_timeout; int /*<<< orphan*/  connection; } ;
struct TYPE_2__ {int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_loopback_async_operation_callback ; 
 struct gb_operation* gb_operation_create (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send (struct gb_operation*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_set_data (struct gb_operation*,struct gb_loopback_async_operation*) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_loopback_async_operation*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 struct gb_loopback_async_operation* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int gb_loopback_async_operation(struct gb_loopback *gb, int type,
				       void *request, int request_size,
				       int response_size,
				       void *completion)
{
	struct gb_loopback_async_operation *op_async;
	struct gb_operation *operation;
	int ret;

	op_async = kzalloc(sizeof(*op_async), GFP_KERNEL);
	if (!op_async)
		return -ENOMEM;

	operation = gb_operation_create(gb->connection, type, request_size,
					response_size, GFP_KERNEL);
	if (!operation) {
		kfree(op_async);
		return -ENOMEM;
	}

	if (request_size)
		memcpy(operation->request->payload, request, request_size);

	gb_operation_set_data(operation, op_async);

	op_async->gb = gb;
	op_async->operation = operation;
	op_async->completion = completion;

	op_async->ts = ktime_get();

	atomic_inc(&gb->outstanding_operations);
	ret = gb_operation_request_send(operation,
					gb_loopback_async_operation_callback,
					jiffies_to_msecs(gb->jiffy_timeout),
					GFP_KERNEL);
	if (ret) {
		atomic_dec(&gb->outstanding_operations);
		gb_operation_put(operation);
		kfree(op_async);
	}
	return ret;
}