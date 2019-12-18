#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* pszResponse; int uiServerError; void* hrServerError; void* hrResult; scalar_t__ dwSocketError; } ;
struct TYPE_12__ {int fDone; TYPE_1__ rIxpResult; int /*<<< orphan*/ * pTransport; } ;
struct TYPE_9__ {int /*<<< orphan*/  vtbl; int /*<<< orphan*/  vtblSMTP2; } ;
struct TYPE_10__ {TYPE_2__ u; scalar_t__ pCallback; scalar_t__ fCommandLogging; } ;
struct TYPE_11__ {TYPE_3__ InetTransport; } ;
typedef  TYPE_4__ SMTPTransport ;
typedef  TYPE_5__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  ISMTPTransport ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  void* HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESP ; 
 int /*<<< orphan*/  ITransportCallback_OnCommand (scalar_t__,int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ *) ; 
 void* IXP_E_SMTP_211_SYSTEM_STATUS ; 
 void* IXP_E_SMTP_214_HELP_MESSAGE ; 
 void* IXP_E_SMTP_220_READY ; 
 void* IXP_E_SMTP_221_CLOSING ; 
 void* IXP_E_SMTP_245_AUTH_SUCCESS ; 
 void* IXP_E_SMTP_250_MAIL_ACTION_OKAY ; 
 void* IXP_E_SMTP_251_FORWARDING_MAIL ; 
 void* IXP_E_SMTP_334_AUTH_READY_RESPONSE ; 
 void* IXP_E_SMTP_354_START_MAIL_INPUT ; 
 void* IXP_E_SMTP_421_NOT_AVAILABLE ; 
 void* IXP_E_SMTP_450_MAILBOX_BUSY ; 
 void* IXP_E_SMTP_451_ERROR_PROCESSING ; 
 void* IXP_E_SMTP_452_NO_SYSTEM_STORAGE ; 
 void* IXP_E_SMTP_454_STARTTLS_FAILED ; 
 void* IXP_E_SMTP_500_SYNTAX_ERROR ; 
 void* IXP_E_SMTP_501_PARAM_SYNTAX ; 
 void* IXP_E_SMTP_502_COMMAND_NOTIMPL ; 
 void* IXP_E_SMTP_503_COMMAND_SEQ ; 
 void* IXP_E_SMTP_504_COMMAND_PARAM_NOTIMPL ; 
 void* IXP_E_SMTP_530_STARTTLS_REQUIRED ; 
 void* IXP_E_SMTP_550_MAILBOX_NOT_FOUND ; 
 void* IXP_E_SMTP_551_USER_NOT_LOCAL ; 
 void* IXP_E_SMTP_552_STORAGE_OVERFLOW ; 
 void* IXP_E_SMTP_553_MAILBOX_NAME_SYNTAX ; 
 void* IXP_E_SMTP_554_TRANSACT_FAILED ; 
 void* IXP_E_SMTP_RESPONSE_ERROR ; 
 void* S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static HRESULT SMTPTransport_ParseResponse(SMTPTransport *This, char *pszResponse, SMTPRESPONSE *pResponse)
{
    HRESULT hrServerError;

    TRACE("response: %s\n", debugstr_a(pszResponse));

    if (!isdigit(*pszResponse))
        return IXP_E_SMTP_RESPONSE_ERROR;
    pResponse->pTransport = (ISMTPTransport *)&This->InetTransport.u.vtblSMTP2;
    pResponse->rIxpResult.pszResponse = pszResponse;
    pResponse->rIxpResult.dwSocketError = 0;
    pResponse->rIxpResult.uiServerError = strtol(pszResponse, &pszResponse, 10);
    pResponse->fDone = (*pszResponse != '-');

    switch (pResponse->rIxpResult.uiServerError)
    {
    case 211: hrServerError = IXP_E_SMTP_211_SYSTEM_STATUS; break;
    case 214: hrServerError = IXP_E_SMTP_214_HELP_MESSAGE; break;
    case 220: hrServerError = IXP_E_SMTP_220_READY; break;
    case 221: hrServerError = IXP_E_SMTP_221_CLOSING; break;
    case 245: hrServerError = IXP_E_SMTP_245_AUTH_SUCCESS; break;
    case 250: hrServerError = IXP_E_SMTP_250_MAIL_ACTION_OKAY; break;
    case 251: hrServerError = IXP_E_SMTP_251_FORWARDING_MAIL; break;
    case 334: hrServerError = IXP_E_SMTP_334_AUTH_READY_RESPONSE; break;
    case 354: hrServerError = IXP_E_SMTP_354_START_MAIL_INPUT; break;
    case 421: hrServerError = IXP_E_SMTP_421_NOT_AVAILABLE; break;
    case 450: hrServerError = IXP_E_SMTP_450_MAILBOX_BUSY; break;
    case 451: hrServerError = IXP_E_SMTP_451_ERROR_PROCESSING; break;
    case 452: hrServerError = IXP_E_SMTP_452_NO_SYSTEM_STORAGE; break;
    case 454: hrServerError = IXP_E_SMTP_454_STARTTLS_FAILED; break;
    case 500: hrServerError = IXP_E_SMTP_500_SYNTAX_ERROR; break;
    case 501: hrServerError = IXP_E_SMTP_501_PARAM_SYNTAX; break;
    case 502: hrServerError = IXP_E_SMTP_502_COMMAND_NOTIMPL; break;
    case 503: hrServerError = IXP_E_SMTP_503_COMMAND_SEQ; break;
    case 504: hrServerError = IXP_E_SMTP_504_COMMAND_PARAM_NOTIMPL; break;
    case 530: hrServerError = IXP_E_SMTP_530_STARTTLS_REQUIRED; break;
    case 550: hrServerError = IXP_E_SMTP_550_MAILBOX_NOT_FOUND; break;
    case 551: hrServerError = IXP_E_SMTP_551_USER_NOT_LOCAL; break;
    case 552: hrServerError = IXP_E_SMTP_552_STORAGE_OVERFLOW; break;
    case 553: hrServerError = IXP_E_SMTP_553_MAILBOX_NAME_SYNTAX; break;
    case 554: hrServerError = IXP_E_SMTP_554_TRANSACT_FAILED; break;
    default:
        hrServerError = IXP_E_SMTP_RESPONSE_ERROR;
        break;
    }
    pResponse->rIxpResult.hrResult = hrServerError;
    pResponse->rIxpResult.hrServerError = hrServerError;

    if (This->InetTransport.pCallback && This->InetTransport.fCommandLogging)
    {
        ITransportCallback_OnCommand(This->InetTransport.pCallback, CMD_RESP,
            pResponse->rIxpResult.pszResponse, hrServerError,
            (IInternetTransport *)&This->InetTransport.u.vtbl);
    }
    return S_OK;
}