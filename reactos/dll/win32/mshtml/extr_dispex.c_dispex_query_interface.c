#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ DispatchEx ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IDispatchJS ; 
 int /*<<< orphan*/  IID_UndocumentedScriptIface ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL dispex_query_interface(DispatchEx *This, REFIID riid, void **ppv)
{
    if(IsEqualGUID(&IID_IDispatch, riid))
        *ppv = &This->IDispatchEx_iface;
    else if(IsEqualGUID(&IID_IDispatchEx, riid))
        *ppv = &This->IDispatchEx_iface;
    else if(IsEqualGUID(&IID_IDispatchJS, riid))
        *ppv = NULL;
    else if(IsEqualGUID(&IID_UndocumentedScriptIface, riid))
        *ppv = NULL;
    else
        return FALSE;

    if(*ppv)
        IUnknown_AddRef((IUnknown*)*ppv);
    return TRUE;
}