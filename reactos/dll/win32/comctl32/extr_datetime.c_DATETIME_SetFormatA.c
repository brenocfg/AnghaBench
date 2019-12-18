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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DATETIME_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DATETIME_SetFormatW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL
DATETIME_SetFormatA (DATETIME_INFO *infoPtr, LPCSTR lpszFormat)
{
    if (lpszFormat) {
	BOOL retval;
	INT len = MultiByteToWideChar(CP_ACP, 0, lpszFormat, -1, NULL, 0);
	LPWSTR wstr = Alloc(len * sizeof(WCHAR));
	if (wstr) MultiByteToWideChar(CP_ACP, 0, lpszFormat, -1, wstr, len);
	retval = DATETIME_SetFormatW (infoPtr, wstr);
	Free (wstr);
	return retval;
    }
    else
	return DATETIME_SetFormatW (infoPtr, 0);

}