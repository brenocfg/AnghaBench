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
typedef  size_t ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Guid; } ;
typedef  size_t* PULONG ;
typedef  TYPE_1__* PGUIDREGINFO ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
ClassFindGuid(
    PGUIDREGINFO GuidList,
    ULONG GuidCount,
    LPGUID Guid,
    PULONG GuidIndex
    )
{
    ULONG i;

    PAGED_CODE();

    for (i = 0; i < GuidCount; i++)
    {
        if (IsEqualGUID(Guid, &GuidList[i].Guid))
        {
            *GuidIndex = i;
            return(TRUE);
        }
    }

    return(FALSE);
}