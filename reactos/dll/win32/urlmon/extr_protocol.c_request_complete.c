#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
struct TYPE_13__ {int /*<<< orphan*/  dwError; scalar_t__ dwResult; } ;
struct TYPE_12__ {int dwState; void* pData; } ;
struct TYPE_11__ {int flags; int bindf; int /*<<< orphan*/  protocol_sink; scalar_t__ request; } ;
typedef  TYPE_1__ Protocol ;
typedef  TYPE_2__ PROTOCOLDATA ;
typedef  TYPE_3__ INTERNET_ASYNC_RESULT ;
typedef  scalar_t__ HINTERNET ;

/* Variables and functions */
 int BINDF_FROMURLMON ; 
 int /*<<< orphan*/  BINDSTATUS_DOWNLOADINGDATA ; 
 int /*<<< orphan*/  BINDSTATUS_ENDDOWNLOADCOMPONENTS ; 
 int FLAG_ERROR ; 
 int FLAG_FIRST_CONTINUE_COMPLETE ; 
 int FLAG_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  IInternetProtocolSink_Switch (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 
 void* UlongToPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  protocol_continue (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void request_complete(Protocol *protocol, INTERNET_ASYNC_RESULT *ar)
{
    PROTOCOLDATA data;

    TRACE("(%p)->(%p)\n", protocol, ar);

    /* PROTOCOLDATA same as native */
    memset(&data, 0, sizeof(data));
    data.dwState = 0xf1000000;

    if(ar->dwResult) {
        protocol->flags |= FLAG_REQUEST_COMPLETE;

        if(!protocol->request) {
            TRACE("setting request handle %p\n", (HINTERNET)ar->dwResult);
            protocol->request = (HINTERNET)ar->dwResult;
        }

        if(protocol->flags & FLAG_FIRST_CONTINUE_COMPLETE)
            data.pData = UlongToPtr(BINDSTATUS_ENDDOWNLOADCOMPONENTS);
        else
            data.pData = UlongToPtr(BINDSTATUS_DOWNLOADINGDATA);

    }else {
        protocol->flags |= FLAG_ERROR;
        data.pData = UlongToPtr(ar->dwError);
    }

    if (protocol->bindf & BINDF_FROMURLMON)
        IInternetProtocolSink_Switch(protocol->protocol_sink, &data);
    else
        protocol_continue(protocol, &data);
}