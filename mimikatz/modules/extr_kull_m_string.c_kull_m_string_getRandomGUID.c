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
struct TYPE_4__ {int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlStringFromGUID (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  UuidCreate (int /*<<< orphan*/ *) ; 

PWSTR kull_m_string_getRandomGUID()
{
	UNICODE_STRING uString;
	GUID guid;
	PWSTR buffer = NULL;
	if(NT_SUCCESS(UuidCreate(&guid)))
	{
		if(NT_SUCCESS(RtlStringFromGUID(&guid, &uString)))
		{
			if(buffer = (PWSTR) LocalAlloc(LPTR, uString.MaximumLength))
				RtlCopyMemory(buffer, uString.Buffer, uString.MaximumLength);
			RtlFreeUnicodeString(&uString);
		}
	}
	return buffer;
}