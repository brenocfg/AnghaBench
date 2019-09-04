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
typedef  int ULONG_PTR ;
struct TYPE_3__ {scalar_t__ Buffer; } ;
typedef  scalar_t__ PWSTR ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PLSA_UNICODE_STRING ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

void kuhl_m_sekurlsa_utils_NlpMakeRelativeOrAbsoluteString(PVOID BaseAddress, PLSA_UNICODE_STRING String, BOOL relative)
{
	if(String->Buffer)
		String->Buffer = (PWSTR) ((ULONG_PTR)(String->Buffer) + ((relative ? -1 : 1) * (ULONG_PTR)(BaseAddress)));
}