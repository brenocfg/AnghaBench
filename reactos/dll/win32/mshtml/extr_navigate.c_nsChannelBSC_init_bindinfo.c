#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  request_data; } ;
struct TYPE_6__ {TYPE_1__ bsc; TYPE_3__* nschannel; } ;
typedef  TYPE_2__ nsChannelBSC ;
struct TYPE_7__ {int /*<<< orphan*/  request_headers; int /*<<< orphan*/  post_data_contains_headers; scalar_t__ post_data_stream; } ;
typedef  TYPE_3__ nsChannel ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* nsChannelBSC_from_BSCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_post_data_stream (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT nsChannelBSC_init_bindinfo(BSCallback *bsc)
{
    nsChannelBSC *This = nsChannelBSC_from_BSCallback(bsc);
    nsChannel *nschannel = This->nschannel;
    HRESULT hres;

    if(nschannel && nschannel->post_data_stream) {
        hres = read_post_data_stream(nschannel->post_data_stream, nschannel->post_data_contains_headers,
                &nschannel->request_headers, &This->bsc.request_data);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}