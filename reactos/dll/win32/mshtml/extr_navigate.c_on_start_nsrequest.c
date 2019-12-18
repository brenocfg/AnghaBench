#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIRequest ;
struct TYPE_9__ {TYPE_5__* window; } ;
struct TYPE_11__ {TYPE_2__ bsc; scalar_t__ is_doc_channel; int /*<<< orphan*/  nscontext; TYPE_3__* nschannel; int /*<<< orphan*/  nslistener; } ;
typedef  TYPE_4__ nsChannelBSC ;
struct TYPE_13__ {scalar_t__ readystate; } ;
struct TYPE_8__ {TYPE_6__* outer_window; } ;
struct TYPE_12__ {TYPE_1__ base; } ;
struct TYPE_10__ {int response_status; int /*<<< orphan*/  nsIHttpChannel_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_ABORT ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ READYSTATE_LOADING ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  nsIStreamListener_OnStartRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ready_state (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  update_window_doc (TYPE_5__*) ; 

__attribute__((used)) static HRESULT on_start_nsrequest(nsChannelBSC *This)
{
    nsresult nsres;

    /* FIXME: it's needed for http connections from BindToObject. */
    if(!This->nschannel->response_status)
        This->nschannel->response_status = 200;

    nsres = nsIStreamListener_OnStartRequest(This->nslistener,
            (nsIRequest*)&This->nschannel->nsIHttpChannel_iface, This->nscontext);
    if(NS_FAILED(nsres)) {
        FIXME("OnStartRequest failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(This->is_doc_channel) {
        if(!This->bsc.window)
            return E_ABORT; /* Binding aborted in OnStartRequest call. */
        update_window_doc(This->bsc.window);
        if(This->bsc.window->base.outer_window->readystate != READYSTATE_LOADING)
            set_ready_state(This->bsc.window->base.outer_window, READYSTATE_LOADING);
    }

    return S_OK;
}