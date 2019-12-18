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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* GetMultiByteString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void REGPROC_write_line(FILE *file, const WCHAR* str, BOOL unicode)
{
    if(unicode)
    {
        fwrite(str, sizeof(WCHAR), lstrlenW(str), file);
    } else
    {
        char* strA = GetMultiByteString(str);
        fputs(strA, file);
        HeapFree(GetProcessHeap(), 0, strA);
    }
}