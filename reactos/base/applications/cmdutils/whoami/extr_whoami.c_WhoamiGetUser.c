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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  EXTENDED_NAME_FORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  CharLowerW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetUserNameExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_PATH ; 

LPWSTR WhoamiGetUser(EXTENDED_NAME_FORMAT NameFormat)
{
    LPWSTR UsrBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH);
    ULONG UsrSiz = MAX_PATH;

    if (UsrBuf == NULL)
        return NULL;

    if (GetUserNameExW(NameFormat, UsrBuf, &UsrSiz))
    {
        CharLowerW(UsrBuf);
        return UsrBuf;
    }

    HeapFree(GetProcessHeap(), 0, UsrBuf);
    return NULL;
}