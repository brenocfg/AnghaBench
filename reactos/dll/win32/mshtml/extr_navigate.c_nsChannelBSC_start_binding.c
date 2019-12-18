#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_6__* window; } ;
struct TYPE_17__ {TYPE_7__ bsc; scalar_t__ is_doc_channel; } ;
typedef  TYPE_8__ nsChannelBSC ;
struct TYPE_14__ {TYPE_4__* outer_window; } ;
struct TYPE_15__ {TYPE_5__ base; } ;
struct TYPE_12__ {TYPE_2__* inner_window; } ;
struct TYPE_13__ {TYPE_3__ base; } ;
struct TYPE_11__ {TYPE_1__* doc; } ;
struct TYPE_10__ {int /*<<< orphan*/  skip_mutation_notif; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_8__* nsChannelBSC_from_BSCallback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT nsChannelBSC_start_binding(BSCallback *bsc)
{
    nsChannelBSC *This = nsChannelBSC_from_BSCallback(bsc);

    if(This->is_doc_channel)
        This->bsc.window->base.outer_window->base.inner_window->doc->skip_mutation_notif = FALSE;

    return S_OK;
}