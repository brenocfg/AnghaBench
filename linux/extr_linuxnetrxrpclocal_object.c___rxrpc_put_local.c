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
struct rxrpc_local {int /*<<< orphan*/  processor; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_queue_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rxrpc_put_local(struct rxrpc_local *local)
{
	_enter("%d", local->debug_id);
	rxrpc_queue_work(&local->processor);
}