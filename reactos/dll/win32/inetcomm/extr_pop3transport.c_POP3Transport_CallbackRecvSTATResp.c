#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  InetTransport; } ;
typedef  TYPE_1__ POP3Transport ;
typedef  int /*<<< orphan*/  IInternetTransport ;

/* Variables and functions */
 int /*<<< orphan*/  InternetTransport_ReadLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP3Transport_CallbackProcessSTATResp ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static void POP3Transport_CallbackRecvSTATResp(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    POP3Transport *This = (POP3Transport *)iface;

    TRACE("\n");
    InternetTransport_ReadLine(&This->InetTransport, POP3Transport_CallbackProcessSTATResp);
}