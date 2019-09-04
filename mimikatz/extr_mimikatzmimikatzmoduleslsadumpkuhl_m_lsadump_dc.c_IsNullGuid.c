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
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {scalar_t__ Data1; scalar_t__ Data2; scalar_t__ Data3; scalar_t__ Data4; } ;
typedef  TYPE_1__ GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL IsNullGuid(GUID* Guid)
{
	if (Guid->Data1 == 0 && Guid->Data2 == 0 && Guid->Data3 == 0 &&
		((ULONG *)Guid->Data4)[0] == 0 && ((ULONG *)Guid->Data4)[1] == 0)
	{
		return TRUE;
	}
	return FALSE;
}