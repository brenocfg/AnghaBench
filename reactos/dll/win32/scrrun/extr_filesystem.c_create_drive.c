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
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct drive {int ref; char* root; TYPE_1__ IDrive_iface; int /*<<< orphan*/  classinfo; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IDrive ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_Drive ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 char* SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drivevtbl ; 
 struct drive* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct drive*) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_drive(WCHAR letter, IDrive **drive)
{
    struct drive *This;

    *drive = NULL;

    This = heap_alloc(sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IDrive_iface.lpVtbl = &drivevtbl;
    This->ref = 1;
    This->root = SysAllocStringLen(NULL, 3);
    if (!This->root)
    {
        heap_free(This);
        return E_OUTOFMEMORY;
    }
    This->root[0] = letter;
    This->root[1] = ':';
    This->root[2] = '\\';
    This->root[3] = 0;

    init_classinfo(&CLSID_Drive, (IUnknown *)&This->IDrive_iface, &This->classinfo);
    *drive = &This->IDrive_iface;
    return S_OK;
}