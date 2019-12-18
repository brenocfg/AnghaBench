#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  IXSLTemplate_iface; } ;
typedef  TYPE_3__ xsltemplate ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {scalar_t__ count; int /*<<< orphan*/  list; } ;
struct TYPE_9__ {int /*<<< orphan*/ * unk; } ;
struct TYPE_12__ {int ref; TYPE_5__ IXSLProcessor_iface; int /*<<< orphan*/  dispex; TYPE_3__* stylesheet; TYPE_2__ params; int /*<<< orphan*/ * outstr; int /*<<< orphan*/  output_type; TYPE_1__ output; int /*<<< orphan*/ * input; } ;
typedef  TYPE_4__ xslprocessor ;
typedef  TYPE_5__ IXSLProcessor ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IXSLTemplate_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROCESSOR_OUTPUT_NOT_SET ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  XSLProcessorVtbl ; 
 TYPE_4__* heap_alloc (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xslprocessor_dispex ; 

HRESULT XSLProcessor_create(xsltemplate *template, IXSLProcessor **ppObj)
{
    xslprocessor *This;

    TRACE("(%p)\n", ppObj);

    This = heap_alloc( sizeof (*This) );
    if(!This)
        return E_OUTOFMEMORY;

    This->IXSLProcessor_iface.lpVtbl = &XSLProcessorVtbl;
    This->ref = 1;
    This->input = NULL;
    This->output.unk = NULL;
    This->output_type = PROCESSOR_OUTPUT_NOT_SET;
    This->outstr = NULL;
    list_init(&This->params.list);
    This->params.count = 0;
    This->stylesheet = template;
    IXSLTemplate_AddRef(&template->IXSLTemplate_iface);
    init_dispex(&This->dispex, (IUnknown*)&This->IXSLProcessor_iface, &xslprocessor_dispex);

    *ppObj = &This->IXSLProcessor_iface;

    TRACE("returning iface %p\n", *ppObj);

    return S_OK;
}