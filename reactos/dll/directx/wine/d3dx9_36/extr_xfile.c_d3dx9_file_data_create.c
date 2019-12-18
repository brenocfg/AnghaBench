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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* lpVtbl; } ;
struct d3dx9_file_data {int ref; unsigned int nb_children; TYPE_1__ ID3DXFileData_iface; TYPE_1__** children; int /*<<< orphan*/  dxfile_data; int /*<<< orphan*/  reference; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* Release ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  IDirectXFileObject ;
typedef  int /*<<< orphan*/  IDirectXFileDataReference ;
typedef  TYPE_1__ ID3DXFileData ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DXFILEERR_NOMOREOBJECTS ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3dx9_file_data*) ; 
 TYPE_1__** HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 scalar_t__ IDirectXFileDataReference_Resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectXFileData_GetNextObject (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IDirectXFileObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDirectXFileData ; 
 int /*<<< orphan*/  IID_IDirectXFileDataReference ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ d3dx9_file_data_vtbl ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static HRESULT d3dx9_file_data_create(IDirectXFileObject *dxfile_object, ID3DXFileData **ret_iface)
{
    struct d3dx9_file_data *object;
    IDirectXFileObject *data_object;
    unsigned int children_array_size = 0;
    HRESULT ret;

    TRACE("dxfile_object %p, ret_iface %p.\n", dxfile_object, ret_iface);

    *ret_iface = NULL;

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*object));
    if (!object)
        return E_OUTOFMEMORY;

    object->ID3DXFileData_iface.lpVtbl = &d3dx9_file_data_vtbl;
    object->ref = 1;

    ret = IDirectXFileObject_QueryInterface(dxfile_object, &IID_IDirectXFileData, (void **)&object->dxfile_data);
    if (FAILED(ret))
    {
        IDirectXFileDataReference *reference;

        ret = IDirectXFileObject_QueryInterface(dxfile_object, &IID_IDirectXFileDataReference, (void **)&reference);
        if (SUCCEEDED(ret))
        {
            ret = IDirectXFileDataReference_Resolve(reference, &object->dxfile_data);
            IUnknown_Release(reference);
            if (FAILED(ret))
            {
                HeapFree(GetProcessHeap(), 0, object);
                return E_FAIL;
            }
            object->reference = TRUE;
        }
        else
        {
            FIXME("Don't know what to do with binary object\n");
            HeapFree(GetProcessHeap(), 0, object);
            return E_FAIL;
        }
    }

    while (SUCCEEDED(ret = IDirectXFileData_GetNextObject(object->dxfile_data, &data_object)))
    {
        if (object->nb_children >= children_array_size)
        {
            ID3DXFileData **new_children;

            if (object->children)
            {
                children_array_size *= 2;
                new_children = HeapReAlloc(GetProcessHeap(), 0, object->children,
                        sizeof(*object->children) * children_array_size);
            }
            else
            {
                children_array_size = 4;
                new_children = HeapAlloc(GetProcessHeap(), 0, sizeof(*object->children) * children_array_size);
            }
            if (!new_children)
            {
                ret = E_OUTOFMEMORY;
                break;
            }
            object->children = new_children;
        }
        ret = d3dx9_file_data_create(data_object, &object->children[object->nb_children]);
        IUnknown_Release(data_object);
        if (FAILED(ret))
            break;
        object->nb_children++;
    }
    if (ret != DXFILEERR_NOMOREOBJECTS)
    {
        (&object->ID3DXFileData_iface)->lpVtbl->Release(&object->ID3DXFileData_iface);
        return ret;
    }
    if (object->children)
    {
        ID3DXFileData **new_children;

        new_children = HeapReAlloc(GetProcessHeap(), 0, object->children,
                sizeof(*object->children) * object->nb_children);
        if (new_children)
            object->children = new_children;
    }

    TRACE("Found %u children\n", object->nb_children);

    *ret_iface = &object->ID3DXFileData_iface;

    return S_OK;
}