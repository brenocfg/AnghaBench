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
struct rxrpc_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_SUCCEEDED ; 
 int __rxrpc_set_call_completion (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool __rxrpc_call_completed(struct rxrpc_call *call)
{
	return __rxrpc_set_call_completion(call, RXRPC_CALL_SUCCEEDED, 0, 0);
}