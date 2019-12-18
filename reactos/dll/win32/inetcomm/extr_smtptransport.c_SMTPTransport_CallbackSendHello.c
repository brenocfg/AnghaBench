#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwFlags; } ;
struct TYPE_13__ {TYPE_2__ ServerInfo; scalar_t__ pCallback; } ;
struct TYPE_9__ {int /*<<< orphan*/  pszResponse; int /*<<< orphan*/  hrServerError; } ;
struct TYPE_12__ {TYPE_1__ rIxpResult; int /*<<< orphan*/  command; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int fESMTP; TYPE_7__ InetTransport; } ;
typedef  TYPE_3__ SMTPTransport ;
typedef  TYPE_4__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  ISMTPCallback ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ISF_QUERYAUTHSUPPORT ; 
 int ISF_QUERYDSNSUPPORT ; 
 int ISF_SSLONSAMEPORT ; 
 int /*<<< orphan*/  ISMTPCallback_OnResponse (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  InternetTransport_DoCommand (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMTPTransport_CallbackRecvHelloResp ; 
 int /*<<< orphan*/  SMTPTransport_ParseResponse (TYPE_3__*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  SMTP_BANNER ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void SMTPTransport_CallbackSendHello(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    SMTPTransport *This = (SMTPTransport *)iface;
    SMTPRESPONSE response = { 0 };
    HRESULT hr;
    const char *pszHello;
    char *pszCommand;
    static const char szHostName[] = "localhost"; /* FIXME */

    TRACE("\n");

    hr = SMTPTransport_ParseResponse(This, pBuffer, &response);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }

    response.command = SMTP_BANNER;
    ISMTPCallback_OnResponse((ISMTPCallback *)This->InetTransport.pCallback, &response);

    if (FAILED(response.rIxpResult.hrServerError))
    {
        ERR("server error: %s\n", debugstr_a(pBuffer));
        /* FIXME: handle error */
        return;
    }

    TRACE("(%s)\n", pBuffer);

    This->fESMTP = strstr(response.rIxpResult.pszResponse, "ESMTP") &&
        This->InetTransport.ServerInfo.dwFlags & (ISF_SSLONSAMEPORT|ISF_QUERYDSNSUPPORT|ISF_QUERYAUTHSUPPORT);

    if (This->fESMTP)
        pszHello = "EHLO ";
    else
        pszHello = "HELO ";

    pszCommand = HeapAlloc(GetProcessHeap(), 0, strlen(pszHello) + strlen(szHostName) + 2);
    strcpy(pszCommand, pszHello);
    strcat(pszCommand, szHostName);
    pszCommand[strlen(pszCommand)+1] = '\0';
    pszCommand[strlen(pszCommand)] = '\n';

    InternetTransport_DoCommand(&This->InetTransport, pszCommand,
        SMTPTransport_CallbackRecvHelloResp);

    HeapFree(GetProcessHeap(), 0, pszCommand);
}