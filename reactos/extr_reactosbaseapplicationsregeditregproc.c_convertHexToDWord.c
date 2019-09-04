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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getAppName () ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BOOL convertHexToDWord(WCHAR* str, DWORD *dw)
{
    char buf[9];
    char dummy;

    WideCharToMultiByte(CP_ACP, 0, str, -1, buf, 9, NULL, NULL);
    if (lstrlenW(str) > 8 || sscanf(buf, "%lx%c", dw, &dummy) != 1) {
        fprintf(stderr,"%S: ERROR, invalid hex value\n", getAppName());
        return FALSE;
    }
    return TRUE;
}