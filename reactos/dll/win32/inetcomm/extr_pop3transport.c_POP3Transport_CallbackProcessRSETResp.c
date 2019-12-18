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
struct TYPE_4__ {scalar_t__ pCallback; } ;
struct TYPE_5__ {TYPE_1__ InetTransport; } ;
typedef  TYPE_2__ POP3Transport ;
typedef  int /*<<< orphan*/  POP3RESPONSE ;
typedef  int /*<<< orphan*/  IPOP3Callback ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPOP3Callback_OnResponse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POP3Transport_ParseResponse (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static void POP3Transport_CallbackProcessRSETResp(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    POP3Transport *This = (POP3Transport *)iface;
    POP3RESPONSE response;
    HRESULT hr;

    TRACE("\n");

    hr = POP3Transport_ParseResponse(This, pBuffer, &response);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }

    IPOP3Callback_OnResponse((IPOP3Callback *)This->InetTransport.pCallback, &response);
}