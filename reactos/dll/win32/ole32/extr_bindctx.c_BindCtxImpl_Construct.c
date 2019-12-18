#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cbStruct; scalar_t__ pServerInfo; int /*<<< orphan*/  locale; int /*<<< orphan*/  dwClassContext; scalar_t__ dwTrackFlags; scalar_t__ dwTickCountDeadline; int /*<<< orphan*/  grfMode; scalar_t__ grfFlags; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bindCtxTable; scalar_t__ bindCtxTableLastIndex; scalar_t__ bindCtxTableSize; TYPE_2__ bindOption2; scalar_t__ ref; TYPE_1__ IBindCtx_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ BindCtxImpl ;
typedef  int /*<<< orphan*/  BIND_OPTS2 ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_SERVER ; 
 int /*<<< orphan*/  GetThreadLocale () ; 
 int /*<<< orphan*/  STGM_READWRITE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  VT_BindCtxImpl ; 

__attribute__((used)) static HRESULT BindCtxImpl_Construct(BindCtxImpl* This)
{
    TRACE("(%p)\n",This);

    /* Initialize the virtual function table.*/
    This->IBindCtx_iface.lpVtbl = &VT_BindCtxImpl;
    This->ref          = 0;

    /* Initialize the BIND_OPTS2 structure */
    This->bindOption2.cbStruct  = sizeof(BIND_OPTS2);
    This->bindOption2.grfFlags = 0;
    This->bindOption2.grfMode = STGM_READWRITE;
    This->bindOption2.dwTickCountDeadline = 0;

    This->bindOption2.dwTrackFlags = 0;
    This->bindOption2.dwClassContext = CLSCTX_SERVER;
    This->bindOption2.locale = GetThreadLocale();
    This->bindOption2.pServerInfo = 0;

    /* Initialize the bindctx table */
    This->bindCtxTableSize=0;
    This->bindCtxTableLastIndex=0;
    This->bindCtxTable = NULL;

    return S_OK;
}