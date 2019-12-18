#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  szTipText; } ;
typedef  TYPE_1__ TOOLTIPS_INFO ;
typedef  int LRESULT ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
TOOLTIPS_OnWMGetText (const TOOLTIPS_INFO *infoPtr, WPARAM size, LPWSTR pszText)
{
    LRESULT res;

    if(!size)
        return 0;

    res = min(strlenW(infoPtr->szTipText)+1, size);
    memcpy(pszText, infoPtr->szTipText, res*sizeof(WCHAR));
    pszText[res-1] = '\0';
    return res-1;
}