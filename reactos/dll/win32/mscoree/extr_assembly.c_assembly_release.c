#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* path; struct TYPE_4__* metadatahdr; int /*<<< orphan*/  hfile; int /*<<< orphan*/  hmap; int /*<<< orphan*/  data; scalar_t__ is_mapped_file; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ ) ; 

HRESULT assembly_release(ASSEMBLY *assembly)
{
    if (!assembly)
        return S_OK;

    if (assembly->is_mapped_file)
    {
        UnmapViewOfFile(assembly->data);
        CloseHandle(assembly->hmap);
        CloseHandle(assembly->hfile);
    }
    HeapFree(GetProcessHeap(), 0, assembly->metadatahdr);
    HeapFree(GetProcessHeap(), 0, assembly->path);
    HeapFree(GetProcessHeap(), 0, assembly);

    return S_OK;
}