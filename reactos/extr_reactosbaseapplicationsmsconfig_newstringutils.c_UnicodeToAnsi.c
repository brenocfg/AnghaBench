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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WC_COMPOSITECHECK ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

LPSTR UnicodeToAnsi(LPCWSTR strW)
{
    LPSTR strA;
    int iNeededChars;

    if (!strW) return NULL;

    iNeededChars = WideCharToMultiByte(CP_ACP,
                                       WC_COMPOSITECHECK /* | WC_NO_BEST_FIT_CHARS */,
                                       strW, -1, NULL, 0, NULL, NULL);

    strA = (LPSTR)MemAlloc(0, iNeededChars * sizeof(CHAR));
    if (!strA) return NULL;

    WideCharToMultiByte(CP_ACP,
                        WC_COMPOSITECHECK /* | WC_NO_BEST_FIT_CHARS */,
                        strW, -1, strA, iNeededChars, NULL, NULL);

    return strA;
}