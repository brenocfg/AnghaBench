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
struct TYPE_3__ {int /*<<< orphan*/ * blobs; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_1__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/ * GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BYTE *assembly_get_blob(ASSEMBLY *assembly, DWORD index, ULONG *size)
{
    return GetData(&assembly->blobs[index], size);
}