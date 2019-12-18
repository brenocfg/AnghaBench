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
struct rxrpc_call {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_IS_SERVICE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool rxrpc_is_service_call(const struct rxrpc_call *call)
{
	return test_bit(RXRPC_CALL_IS_SERVICE, &call->flags);
}