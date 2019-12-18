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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BUFFILE ; 
 int /*<<< orphan*/  GetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edt1 ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void FD31_StripEditControl(HWND hwnd)
{
    WCHAR temp[BUFFILE], *cp;

    GetDlgItemTextW( hwnd, edt1, temp, ARRAY_SIZE(temp));
    cp = wcsrchr(temp, '\\');
    if (cp != NULL) {
	lstrcpyW(temp, cp+1);
    }
    cp = wcsrchr(temp, ':');
    if (cp != NULL) {
	lstrcpyW(temp, cp+1);
    }
    /* FIXME: shouldn't we do something with the result here? ;-) */
}