#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szCommandFormat ;
struct TYPE_9__ {int /*<<< orphan*/  hrServerError; } ;
struct TYPE_14__ {TYPE_1__ rIxpResult; } ;
struct TYPE_11__ {size_t cAddress; TYPE_2__* prgAddress; } ;
struct TYPE_12__ {TYPE_3__ rAddressList; } ;
struct TYPE_13__ {size_t ulCurrentAddressIndex; int /*<<< orphan*/  InetTransport; TYPE_4__ pending_message; } ;
struct TYPE_10__ {int addrtype; int /*<<< orphan*/  szEmail; } ;
typedef  TYPE_5__ SMTPTransport ;
typedef  TYPE_6__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ADDR_TO ; 
 int ADDR_TOFROM_MASK ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InternetTransport_DoCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMTPTransport_CallbackMessageReadDataResponse ; 
 int /*<<< orphan*/  SMTPTransport_CallbackMessageReadToResponse ; 
 int /*<<< orphan*/  SMTPTransport_ParseResponse (TYPE_5__*,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SMTPTransport_CallbackMessageSendTo(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    SMTPTransport *This = (SMTPTransport *)iface;
    SMTPRESPONSE response;
    HRESULT hr;

    TRACE("\n");

    hr = SMTPTransport_ParseResponse(This, pBuffer, &response);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }

    if (FAILED(response.rIxpResult.hrServerError))
    {
        ERR("server error: %s\n", debugstr_a(pBuffer));
        /* FIXME: handle error */
        return;
    }

    for (; This->ulCurrentAddressIndex < This->pending_message.rAddressList.cAddress; This->ulCurrentAddressIndex++)
    {
        TRACE("address[%d]: %s\n", This->ulCurrentAddressIndex,
            This->pending_message.rAddressList.prgAddress[This->ulCurrentAddressIndex].szEmail);

        if ((This->pending_message.rAddressList.prgAddress[This->ulCurrentAddressIndex].addrtype & ADDR_TOFROM_MASK) == ADDR_TO)
        {
            static const char szCommandFormat[] = "RCPT TO: <%s>\n";
            char *szCommand;
            int len = sizeof(szCommandFormat) - 2 /* "%s" */ +
                strlen(This->pending_message.rAddressList.prgAddress[This->ulCurrentAddressIndex].szEmail);

            szCommand = HeapAlloc(GetProcessHeap(), 0, len);
            if (!szCommand)
                return;

            sprintf(szCommand, szCommandFormat,
                This->pending_message.rAddressList.prgAddress[This->ulCurrentAddressIndex].szEmail);

            This->ulCurrentAddressIndex++;
            hr = InternetTransport_DoCommand(&This->InetTransport, szCommand,
                SMTPTransport_CallbackMessageReadToResponse);

            HeapFree(GetProcessHeap(), 0, szCommand);
            return;
        }
    }

    hr = InternetTransport_DoCommand(&This->InetTransport, "DATA\n",
        SMTPTransport_CallbackMessageReadDataResponse);
}