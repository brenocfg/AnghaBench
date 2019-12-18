#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; TYPE_3__ IErrorInfo_iface; scalar_t__ m_dwHelpContext; int /*<<< orphan*/ * help_file; int /*<<< orphan*/ * description; int /*<<< orphan*/ * source; TYPE_1__ ISupportErrorInfo_iface; TYPE_2__ ICreateErrorInfo_iface; } ;
typedef  TYPE_3__ IErrorInfo ;
typedef  TYPE_4__ ErrorInfoImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CreateErrorInfoVtbl ; 
 int /*<<< orphan*/  ErrorInfoVtbl ; 
 int /*<<< orphan*/  SupportErrorInfoVtbl ; 
 TYPE_4__* heap_alloc (int) ; 

__attribute__((used)) static IErrorInfo* IErrorInfoImpl_Constructor(void)
{
    ErrorInfoImpl *This = heap_alloc(sizeof(ErrorInfoImpl));

    if (!This) return NULL;

    This->IErrorInfo_iface.lpVtbl = &ErrorInfoVtbl;
    This->ICreateErrorInfo_iface.lpVtbl = &CreateErrorInfoVtbl;
    This->ISupportErrorInfo_iface.lpVtbl = &SupportErrorInfoVtbl;
    This->ref = 1;
    This->source = NULL;
    This->description = NULL;
    This->help_file = NULL;
    This->m_dwHelpContext = 0;

    return &This->IErrorInfo_iface;
}