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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  FILESYSTEM_STATISTICS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stderr ; 

inline int
ValidateSizes(ULONG Length, DWORD ProcCount, DWORD BytesRead, DWORD SpecificSize)
{
    /* Check whether we could read our base length for every processor */
    if (Length * ProcCount > BytesRead)
    {
        _ftprintf(stderr, _T("Only performed a partial read: %lu (expected: %lu)\n"), BytesRead, Length * ProcCount);
        return 1;
    }

    /* Check whether this covers a specific entry and a generic entry for every processor */
    if ((sizeof(FILESYSTEM_STATISTICS) + SpecificSize) * ProcCount > BytesRead)
    {
        _ftprintf(stderr, _T("Only performed a partial read: %lu (expected: %lu)\n"), BytesRead, (sizeof(FILESYSTEM_STATISTICS) + SpecificSize));
        return 1;
    }

    return 0;
}