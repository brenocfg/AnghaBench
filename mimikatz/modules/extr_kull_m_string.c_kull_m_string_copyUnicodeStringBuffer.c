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
struct TYPE_4__ {scalar_t__ MaximumLength; scalar_t__ Buffer; } ;
typedef  scalar_t__ PWSTR ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL kull_m_string_copyUnicodeStringBuffer(PUNICODE_STRING pSource, PUNICODE_STRING pDestination)
{
	BOOL status = FALSE;
	if(pSource && pDestination && pSource->MaximumLength && pSource->Buffer)
	{
		*pDestination = *pSource;
		if(pDestination->Buffer = (PWSTR) LocalAlloc(LPTR, pSource->MaximumLength))
		{
			status = TRUE;
			RtlCopyMemory(pDestination->Buffer, pSource->Buffer, pSource->MaximumLength);
		}
	}
	return status;
}