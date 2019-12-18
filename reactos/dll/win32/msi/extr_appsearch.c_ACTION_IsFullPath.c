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
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char toupperW (char) ; 

__attribute__((used)) static BOOL ACTION_IsFullPath(LPCWSTR path)
{
    WCHAR first = toupperW(path[0]);
    BOOL ret;

    if (first >= 'A' && first <= 'Z' && path[1] == ':')
        ret = TRUE;
    else if (path[0] == '\\' && path[1] == '\\')
        ret = TRUE;
    else
        ret = FALSE;
    return ret;
}