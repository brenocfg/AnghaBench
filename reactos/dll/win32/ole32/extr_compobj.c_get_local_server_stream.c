#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cs; TYPE_2__* local_server; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; int /*<<< orphan*/  marshal_stream; TYPE_1__ IServiceProvider_iface; TYPE_3__* apt; } ;
typedef  TYPE_2__ LocalServer ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  CoMarshalInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IStream_Clone (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalServerVtbl ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int /*<<< orphan*/  MSHLFLAGS_TABLESTRONG ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static HRESULT get_local_server_stream(APARTMENT *apt, IStream **ret)
{
    HRESULT hres = S_OK;

    EnterCriticalSection(&apt->cs);

    if(!apt->local_server) {
        LocalServer *obj;

        obj = heap_alloc(sizeof(*obj));
        if(obj) {
            obj->IServiceProvider_iface.lpVtbl = &LocalServerVtbl;
            obj->ref = 1;
            obj->apt = apt;

            hres = CreateStreamOnHGlobal(0, TRUE, &obj->marshal_stream);
            if(SUCCEEDED(hres)) {
                hres = CoMarshalInterface(obj->marshal_stream, &IID_IServiceProvider, (IUnknown*)&obj->IServiceProvider_iface,
                        MSHCTX_LOCAL, NULL, MSHLFLAGS_TABLESTRONG);
                if(FAILED(hres))
                    IStream_Release(obj->marshal_stream);
            }

            if(SUCCEEDED(hres))
                apt->local_server = obj;
            else
                heap_free(obj);
        }else {
            hres = E_OUTOFMEMORY;
        }
    }

    if(SUCCEEDED(hres))
        hres = IStream_Clone(apt->local_server->marshal_stream, ret);

    LeaveCriticalSection(&apt->cs);

    if(FAILED(hres))
        ERR("Failed: %08x\n", hres);
    return hres;
}