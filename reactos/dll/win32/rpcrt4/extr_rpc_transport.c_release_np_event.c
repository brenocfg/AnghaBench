#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  event_cache; } ;
typedef  TYPE_1__ RpcConnection_np ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ InterlockedExchangePointer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void release_np_event(RpcConnection_np *connection, HANDLE event)
{
    event = InterlockedExchangePointer(&connection->event_cache, event);
    if (event)
        CloseHandle(event);
}