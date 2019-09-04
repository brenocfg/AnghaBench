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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  scalar_t__ WORD ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WORD
GetCBSelectedMonth(HWND hCombo)
{
    INT i;
    WORD Ret = (WORD)-1;

    i = (INT)SendMessageW(hCombo,
                          CB_GETCURSEL,
                          0,
                          0);
    if (i != CB_ERR)
    {
        i = (INT)SendMessageW(hCombo,
                              CB_GETITEMDATA,
                              (WPARAM)i,
                              0);

        if (i >= 1 && i <= 13)
            Ret = (WORD)i;
    }

    return Ret;
}