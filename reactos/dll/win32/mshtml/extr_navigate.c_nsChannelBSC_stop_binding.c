#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nschannel; scalar_t__ is_doc_channel; } ;
typedef  TYPE_1__ nsChannelBSC ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  E_ABORT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  async_stop_request (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_navigation_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* nsChannelBSC_from_BSCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_stop_nsrequest (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT nsChannelBSC_stop_binding(BSCallback *bsc, HRESULT result)
{
    nsChannelBSC *This = nsChannelBSC_from_BSCallback(bsc);

    if(result != E_ABORT) {
        if(FAILED(result))
            handle_navigation_error(This, result);
        else if(This->is_doc_channel && This->nschannel) {
            result = async_stop_request(This);
            if(SUCCEEDED(result))
                return S_OK;
        }
    }

    on_stop_nsrequest(This, result);
    return S_OK;
}