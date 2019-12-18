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
struct TYPE_4__ {int runContext; int /*<<< orphan*/  classObject; int /*<<< orphan*/  RpcRegistration; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ RegisteredClass ;

/* Variables and functions */
 int CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_StopLocalServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void COM_RevokeRegisteredClassObject(RegisteredClass *curClass)
{
    list_remove(&curClass->entry);

    if (curClass->runContext & CLSCTX_LOCAL_SERVER)
        RPC_StopLocalServer(curClass->RpcRegistration);

    IUnknown_Release(curClass->classObject);
    HeapFree(GetProcessHeap(), 0, curClass);
}