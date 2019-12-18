#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int* PWCHAR ;
typedef  int /*<<< orphan*/  PCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  wcsncpy (int*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static
VOID
NtfsWSubString(PWCHAR pTarget,
               PCWSTR pSource,
               size_t pLength)
{
    wcsncpy(pTarget, pSource, pLength);
    pTarget[pLength] = L'\0';
}