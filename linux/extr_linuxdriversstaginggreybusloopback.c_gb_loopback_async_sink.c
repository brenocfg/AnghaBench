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
typedef  scalar_t__ u32 ;
struct gb_loopback_transfer_request {int /*<<< orphan*/  len; } ;
struct gb_loopback {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_LOOPBACK_TYPE_SINK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int gb_loopback_async_operation (struct gb_loopback*,int /*<<< orphan*/ ,struct gb_loopback_transfer_request*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gb_loopback_transfer_request*) ; 
 struct gb_loopback_transfer_request* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_loopback_async_sink(struct gb_loopback *gb, u32 len)
{
	struct gb_loopback_transfer_request *request;
	int retval;

	request = kmalloc(len + sizeof(*request), GFP_KERNEL);
	if (!request)
		return -ENOMEM;

	request->len = cpu_to_le32(len);
	retval = gb_loopback_async_operation(gb, GB_LOOPBACK_TYPE_SINK,
					     request, len + sizeof(*request),
					     0, NULL);
	kfree(request);
	return retval;
}