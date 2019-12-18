#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ CallsCompletedEvent; scalar_t__ Delete; int /*<<< orphan*/  CurrentCalls; } ;
typedef  TYPE_1__ RpcServerInterface ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 

__attribute__((used)) static void RPCRT4_release_server_interface(RpcServerInterface *sif)
{
  if (!InterlockedDecrement(&sif->CurrentCalls) &&
      sif->Delete) {
    /* sif must have been removed from server_interfaces before
     * CallsCompletedEvent is set */
    if (sif->CallsCompletedEvent)
      SetEvent(sif->CallsCompletedEvent);
    HeapFree(GetProcessHeap(), 0, sif);
  }
}