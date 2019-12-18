#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mesh_data {size_t num_materials; TYPE_1__* material_indices; TYPE_1__* materials; } ;
struct TYPE_2__ {struct TYPE_2__* pTextureFilename; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void destroy_materials(struct mesh_data *mesh)
{
    DWORD i;
    for (i = 0; i < mesh->num_materials; i++)
        HeapFree(GetProcessHeap(), 0, mesh->materials[i].pTextureFilename);
    HeapFree(GetProcessHeap(), 0, mesh->materials);
    HeapFree(GetProcessHeap(), 0, mesh->material_indices);
    mesh->num_materials = 0;
    mesh->materials = NULL;
    mesh->material_indices = NULL;
}