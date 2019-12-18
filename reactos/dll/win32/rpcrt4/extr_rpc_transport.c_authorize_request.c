#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct authinfo {scalar_t__ scheme; scalar_t__ finished; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
typedef  char WCHAR ;
struct TYPE_10__ {TYPE_3__* QOS; } ;
struct TYPE_11__ {int /*<<< orphan*/  cancel_event; int /*<<< orphan*/  async_data; TYPE_4__ common; int /*<<< orphan*/  servername; } ;
struct TYPE_9__ {TYPE_2__* qos; } ;
struct TYPE_7__ {int /*<<< orphan*/  HttpCredentials; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_5__ RpcConnection_http ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  HINTERNET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int HTTP_ADDREQ_FLAG_ADD ; 
 int HTTP_ADDREQ_FLAG_REPLACE ; 
 int /*<<< orphan*/  HttpAddRequestHeadersW (int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  HttpSendRequestW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_C_HTTP_AUTHN_SCHEME_BASIC ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  destroy_authinfo (struct authinfo*) ; 
 scalar_t__ do_authorization (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct authinfo**) ; 
 int /*<<< orphan*/  drain_content (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ insert_authorization_header (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_async_request (int /*<<< orphan*/ ) ; 
 scalar_t__ rpcrt4_http_check_response (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_async_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS authorize_request(RpcConnection_http *httpc, HINTERNET request)
{
    static const WCHAR authW[] = {'A','u','t','h','o','r','i','z','a','t','i','o','n',':','\r','\n',0};
    struct authinfo *info = NULL;
    RPC_STATUS status;
    BOOL ret;

    for (;;)
    {
        status = do_authorization(request, httpc->servername, httpc->common.QOS->qos->u.HttpCredentials, &info);
        if (status != RPC_S_OK) break;

        status = insert_authorization_header(request, info->scheme, info->data, info->data_len);
        if (status != RPC_S_OK) break;

        prepare_async_request(httpc->async_data);
        ret = HttpSendRequestW(request, NULL, 0, NULL, 0);
        status = wait_async_request(httpc->async_data, ret, httpc->cancel_event);
        if (status != RPC_S_OK || info->finished) break;

        status = rpcrt4_http_check_response(request);
        if (status != RPC_S_OK && status != ERROR_ACCESS_DENIED) break;
        drain_content(request, httpc->async_data, httpc->cancel_event);
    }

    if (info->scheme != RPC_C_HTTP_AUTHN_SCHEME_BASIC)
        HttpAddRequestHeadersW(request, authW, -1, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);

    destroy_authinfo(info);
    return status;
}