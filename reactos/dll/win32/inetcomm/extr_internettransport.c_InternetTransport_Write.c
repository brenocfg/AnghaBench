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
struct TYPE_5__ {scalar_t__ Status; TYPE_1__ u; int /*<<< orphan*/  Socket; scalar_t__ fnCompletion; } ;
typedef  TYPE_2__ InternetTransport ;
typedef  int /*<<< orphan*/  (* INETXPORT_COMPLETION_FUNCTION ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXP_DISCONNECTED ; 
 int /*<<< orphan*/  IXP_E_BUSY ; 
 int /*<<< orphan*/  IXP_E_NOT_CONNECTED ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

HRESULT InternetTransport_Write(InternetTransport *This, const char *pvData,
    int cbSize, INETXPORT_COMPLETION_FUNCTION fnCompletion)
{
    int ret;

    if (This->Status == IXP_DISCONNECTED)
        return IXP_E_NOT_CONNECTED;

    if (This->fnCompletion)
        return IXP_E_BUSY;

    /* FIXME: do this asynchronously */
    ret = send(This->Socket, pvData, cbSize, 0);
    if (ret == SOCKET_ERROR)
    {
        ERR("send failed with error %d\n", WSAGetLastError());
        /* FIXME: handle error */
    }

    fnCompletion((IInternetTransport *)&This->u.vtbl, NULL, 0);

    return S_OK;
}