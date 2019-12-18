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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIRequest ;
struct TYPE_5__ {TYPE_1__* nschannel; int /*<<< orphan*/  nscontext; scalar_t__ nslistener; } ;
typedef  TYPE_2__ nsChannelBSC ;
struct TYPE_4__ {int /*<<< orphan*/  nsIHttpChannel_iface; scalar_t__ load_group; } ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
#define  E_ABORT 129 
 int /*<<< orphan*/  NS_BINDING_ABORTED ; 
 int /*<<< orphan*/  NS_ERROR_FAILURE ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_OK ; 
#define  S_OK 128 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsILoadGroup_RemoveRequest (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIStreamListener_OnStopRequest (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_stop_nsrequest(nsChannelBSC *This, HRESULT result)
{
    nsresult nsres, request_result;

    switch(result) {
    case S_OK:
        request_result = NS_OK;
        break;
    case E_ABORT:
        request_result = NS_BINDING_ABORTED;
        break;
    default:
        request_result = NS_ERROR_FAILURE;
    }

    if(This->nslistener) {
        nsres = nsIStreamListener_OnStopRequest(This->nslistener,
                 (nsIRequest*)&This->nschannel->nsIHttpChannel_iface, This->nscontext,
                 request_result);
        if(NS_FAILED(nsres))
            WARN("OnStopRequest failed: %08x\n", nsres);
    }

    if(This->nschannel && This->nschannel->load_group) {
        nsres = nsILoadGroup_RemoveRequest(This->nschannel->load_group,
                (nsIRequest*)&This->nschannel->nsIHttpChannel_iface, NULL, request_result);
        if(NS_FAILED(nsres))
            ERR("RemoveRequest failed: %08x\n", nsres);
    }
}