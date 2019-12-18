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
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * doc_host; int /*<<< orphan*/ * outer; TYPE_2__ IWebBrowserPriv2IE9_iface; TYPE_1__ ITargetFramePriv2_iface; TYPE_5__ ITargetFrame2_iface; TYPE_4__ ITargetFrame_iface; TYPE_3__ IHlinkFrame_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_6__ HlinkFrame ;
typedef  int /*<<< orphan*/  DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  HlinkFrameVtbl ; 
 int /*<<< orphan*/  TargetFrame2Vtbl ; 
 int /*<<< orphan*/  TargetFramePriv2Vtbl ; 
 int /*<<< orphan*/  TargetFrameVtbl ; 
 int /*<<< orphan*/  WebBrowserPriv2IE9Vtbl ; 

void HlinkFrame_Init(HlinkFrame *This, IUnknown *outer, DocHost *doc_host)
{
    This->IHlinkFrame_iface.lpVtbl = &HlinkFrameVtbl;
    This->ITargetFrame_iface.lpVtbl = &TargetFrameVtbl;
    This->ITargetFrame2_iface.lpVtbl = &TargetFrame2Vtbl;
    This->ITargetFramePriv2_iface.lpVtbl = &TargetFramePriv2Vtbl;
    This->IWebBrowserPriv2IE9_iface.lpVtbl = &WebBrowserPriv2IE9Vtbl;

    This->outer = outer;
    This->doc_host = doc_host;
}