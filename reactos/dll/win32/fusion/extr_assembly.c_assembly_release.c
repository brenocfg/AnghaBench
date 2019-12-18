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
struct TYPE_4__ {int /*<<< orphan*/  hfile; int /*<<< orphan*/  hmap; int /*<<< orphan*/  data; struct TYPE_4__* path; struct TYPE_4__* metadatahdr; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

HRESULT assembly_release(ASSEMBLY *assembly)
{
    if (!assembly)
        return S_OK;

    heap_free(assembly->metadatahdr);
    heap_free(assembly->path);
    UnmapViewOfFile(assembly->data);
    CloseHandle(assembly->hmap);
    CloseHandle(assembly->hfile);
    heap_free(assembly);

    return S_OK;
}