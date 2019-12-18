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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_MAX_PATHLEN ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL _chm_parse_UTF8(UChar **pEntry, UInt64 count, WCHAR *path)
{
    DWORD length = MultiByteToWideChar(CP_UTF8, 0, (char *)*pEntry, count, path, CHM_MAX_PATHLEN);
    path[length] = '\0';
    *pEntry += count;
    return !!length;
}