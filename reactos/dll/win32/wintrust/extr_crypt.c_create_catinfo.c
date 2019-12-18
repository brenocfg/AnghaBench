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
struct catinfo {int /*<<< orphan*/  magic; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  struct catinfo* HCATINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CATINFO_MAGIC ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct catinfo* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct catinfo* INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HCATINFO create_catinfo(const WCHAR *filename)
{
    struct catinfo *ci;

    if (!(ci = HeapAlloc(GetProcessHeap(), 0, sizeof(*ci))))
    {
        SetLastError(ERROR_OUTOFMEMORY);
        return INVALID_HANDLE_VALUE;
    }
    strcpyW(ci->file, filename);
    ci->magic = CATINFO_MAGIC;
    return ci;
}