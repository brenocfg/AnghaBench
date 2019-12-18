#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vtbl; } ;
struct TYPE_5__ {TYPE_1__ u; scalar_t__ pCallback; int /*<<< orphan*/  Status; } ;
typedef  TYPE_2__ InternetTransport ;
typedef  int /*<<< orphan*/  IXPSTATUS ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ITransportCallback_OnStatus (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT InternetTransport_ChangeStatus(InternetTransport *This, IXPSTATUS Status)
{
    This->Status = Status;
    if (This->pCallback)
        ITransportCallback_OnStatus(This->pCallback, Status,
            (IInternetTransport *)&This->u.vtbl);
    return S_OK;
}