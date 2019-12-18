#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  token_value_len; int /*<<< orphan*/  token_name_len; int /*<<< orphan*/  post_action_len; } ;
typedef  TYPE_10__ sl_NetAppHttpServerPostToken_t ;
struct TYPE_21__ {int /*<<< orphan*/  token_name_len; } ;
typedef  TYPE_11__ sl_NetAppHttpServerGetToken_t ;
struct TYPE_22__ {int /*<<< orphan*/ * token_value; int /*<<< orphan*/  name_len; int /*<<< orphan*/  value_len; int /*<<< orphan*/ * token_name; } ;
typedef  TYPE_12__ slHttpServerData_t ;
typedef  int /*<<< orphan*/  _u8 ;
struct TYPE_34__ {int Opcode; } ;
struct TYPE_23__ {TYPE_9__ GenHeader; } ;
typedef  TYPE_13__ _SlResponseHeader_t ;
struct TYPE_31__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_30__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_29__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_32__ {TYPE_6__ token_value; TYPE_5__ token_name; TYPE_4__ action; } ;
struct TYPE_26__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_33__ {TYPE_7__ httpPostData; TYPE_1__ httpTokenName; } ;
struct TYPE_27__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_28__ {TYPE_2__ token_value; } ;
struct TYPE_25__ {TYPE_8__ EventData; int /*<<< orphan*/  Event; } ;
struct TYPE_24__ {int /*<<< orphan*/  Response; TYPE_3__ ResponseData; } ;
typedef  TYPE_14__ SlHttpServerResponse_t ;
typedef  TYPE_15__ SlHttpServerEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TOKEN_NAME_LEN ; 
 int /*<<< orphan*/  MAX_TOKEN_VALUE_LEN ; 
 int /*<<< orphan*/  MSG_305 ; 
 int /*<<< orphan*/  SL_ERROR_TRACE2 (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  SL_NETAPP_HTTPGETTOKENVALUE_EVENT ; 
 int /*<<< orphan*/  SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT ; 
 int /*<<< orphan*/  SL_NETAPP_HTTPSETTOKENVALUE ; 
 int /*<<< orphan*/  SL_NETAPP_RESPONSE_NONE ; 
#define  SL_OPCODE_NETAPP_DNSGETHOSTBYNAMEASYNCRESPONSE 134 
#define  SL_OPCODE_NETAPP_DNSGETHOSTBYNAMEASYNCRESPONSE_V6 133 
#define  SL_OPCODE_NETAPP_HTTPGETTOKENVALUE 132 
#define  SL_OPCODE_NETAPP_HTTPPOSTTOKENVALUE 131 
#define  SL_OPCODE_NETAPP_MDNSGETHOSTBYSERVICEASYNCRESPONSE 130 
#define  SL_OPCODE_NETAPP_MDNSGETHOSTBYSERVICEASYNCRESPONSE_V6 129 
#define  SL_OPCODE_NETAPP_PINGREPORTREQUESTRESPONSE 128 
 int /*<<< orphan*/  VERIFY_PROTOCOL (int /*<<< orphan*/ ) ; 
 scalar_t__ _SL_RESP_ARGS_START (TYPE_13__*) ; 
 int /*<<< orphan*/  _SlDrvHandleHttpServerEvents (TYPE_15__*,TYPE_14__*) ; 
 int /*<<< orphan*/  _sl_HandleAsync_DnsGetHostByName (void*) ; 
 int /*<<< orphan*/  _sl_HandleAsync_DnsGetHostByService (void*) ; 
 int /*<<< orphan*/  _sl_HandleAsync_PingResponse (void*) ; 
 int /*<<< orphan*/  _sl_NetAppSendTokenValue (TYPE_12__*) ; 

void _SlDrvNetAppEventHandler(void* pArgs)
{
    _SlResponseHeader_t     *pHdr       = (_SlResponseHeader_t *)pArgs;
#if defined(sl_HttpServerCallback) || defined(EXT_LIB_REGISTERED_HTTP_SERVER_EVENTS)
    SlHttpServerEvent_t		httpServerEvent;
    SlHttpServerResponse_t	httpServerResponse;
#endif
    
    switch(pHdr->GenHeader.Opcode)
    {
        case SL_OPCODE_NETAPP_DNSGETHOSTBYNAMEASYNCRESPONSE:
        case SL_OPCODE_NETAPP_DNSGETHOSTBYNAMEASYNCRESPONSE_V6:
            _sl_HandleAsync_DnsGetHostByName(pArgs);
            break;
#ifndef SL_TINY_EXT            
        case SL_OPCODE_NETAPP_MDNSGETHOSTBYSERVICEASYNCRESPONSE:
        case SL_OPCODE_NETAPP_MDNSGETHOSTBYSERVICEASYNCRESPONSE_V6:
            _sl_HandleAsync_DnsGetHostByService(pArgs);
            break;
        case SL_OPCODE_NETAPP_PINGREPORTREQUESTRESPONSE:
            _sl_HandleAsync_PingResponse(pArgs);
            break;
#endif

#if defined(sl_HttpServerCallback) || defined(EXT_LIB_REGISTERED_HTTP_SERVER_EVENTS)
		case SL_OPCODE_NETAPP_HTTPGETTOKENVALUE:
		{              
			_u8 *pTokenName;
			slHttpServerData_t Token_value;
			sl_NetAppHttpServerGetToken_t *httpGetToken = (sl_NetAppHttpServerGetToken_t *)_SL_RESP_ARGS_START(pHdr);
                        pTokenName = (_u8 *)((sl_NetAppHttpServerGetToken_t *)httpGetToken + 1);

			httpServerResponse.Response = SL_NETAPP_HTTPSETTOKENVALUE;
			httpServerResponse.ResponseData.token_value.len = MAX_TOKEN_VALUE_LEN;

            /* Reuse the async buffer for getting the token value response from the user */
			httpServerResponse.ResponseData.token_value.data = (_u8 *)_SL_RESP_ARGS_START(pHdr) + MAX_TOKEN_NAME_LEN;

            httpServerEvent.Event = SL_NETAPP_HTTPGETTOKENVALUE_EVENT;
			httpServerEvent.EventData.httpTokenName.len = httpGetToken->token_name_len;
			httpServerEvent.EventData.httpTokenName.data = pTokenName;

			Token_value.token_name =  pTokenName;

            _SlDrvHandleHttpServerEvents (&httpServerEvent, &httpServerResponse);			

			Token_value.value_len = httpServerResponse.ResponseData.token_value.len;
			Token_value.name_len = httpServerEvent.EventData.httpTokenName.len;
			Token_value.token_value = httpServerResponse.ResponseData.token_value.data;
			    

			_sl_NetAppSendTokenValue(&Token_value);
		}
		break;

		case SL_OPCODE_NETAPP_HTTPPOSTTOKENVALUE:
		{
			_u8 *pPostParams;

			sl_NetAppHttpServerPostToken_t *httpPostTokenArgs = (sl_NetAppHttpServerPostToken_t *)_SL_RESP_ARGS_START(pHdr);
			pPostParams = (_u8 *)((sl_NetAppHttpServerPostToken_t *)httpPostTokenArgs + 1);

			httpServerEvent.Event = SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT;

			httpServerEvent.EventData.httpPostData.action.len = httpPostTokenArgs->post_action_len;
			httpServerEvent.EventData.httpPostData.action.data = pPostParams;
			pPostParams+=httpPostTokenArgs->post_action_len;

			httpServerEvent.EventData.httpPostData.token_name.len = httpPostTokenArgs->token_name_len;
			httpServerEvent.EventData.httpPostData.token_name.data = pPostParams;
			pPostParams+=httpPostTokenArgs->token_name_len;

			httpServerEvent.EventData.httpPostData.token_value.len = httpPostTokenArgs->token_value_len;
			httpServerEvent.EventData.httpPostData.token_value.data = pPostParams;

			httpServerResponse.Response = SL_NETAPP_RESPONSE_NONE;

            _SlDrvHandleHttpServerEvents (&httpServerEvent, &httpServerResponse);
			
		}
		break;
#endif

        
        default:
            SL_ERROR_TRACE2(MSG_305, "ASSERT: _SlDrvNetAppEventHandler : invalid opcode = 0x%x = %1", pHdr->GenHeader.Opcode, pHdr->GenHeader.Opcode);
            VERIFY_PROTOCOL(0);
    }
}