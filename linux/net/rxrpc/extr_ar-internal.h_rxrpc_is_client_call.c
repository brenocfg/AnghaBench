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
 int /*<<< orphan*/  rxrpc_is_service_call (struct rxrpc_call const*) ; 

__attribute__((used)) static inline bool rxrpc_is_client_call(const struct rxrpc_call *call)
{
	return !rxrpc_is_service_call(call);
}