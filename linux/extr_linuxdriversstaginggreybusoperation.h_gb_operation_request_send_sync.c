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
struct gb_operation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_OPERATION_TIMEOUT_DEFAULT ; 
 int gb_operation_request_send_sync_timeout (struct gb_operation*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
gb_operation_request_send_sync(struct gb_operation *operation)
{
	return gb_operation_request_send_sync_timeout(operation,
			GB_OPERATION_TIMEOUT_DEFAULT);
}