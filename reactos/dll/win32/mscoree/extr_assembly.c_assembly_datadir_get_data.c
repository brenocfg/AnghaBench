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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  VirtualAddress; } ;
typedef  TYPE_1__ IMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  ASSEMBLY ;

/* Variables and functions */
 void* assembly_rva_to_va (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ULONG assembly_datadir_get_data(ASSEMBLY *assembly,
    IMAGE_DATA_DIRECTORY *datadir, void **data)
{
    if (!datadir->VirtualAddress || !datadir->Size)
    {
        *data = NULL;
        return 0;
    }
    else
    {
        *data = assembly_rva_to_va(assembly, datadir->VirtualAddress);
        return datadir->Size;
    }
}