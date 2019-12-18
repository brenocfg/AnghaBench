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

/* Variables and functions */
 int GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LOCALE_STHOUSAND ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 

__attribute__((used)) static WCHAR UPDOWN_GetThousandSep(void)
{
    WCHAR sep[2];

    if(GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, sep, 2) != 1)
        sep[0] = ',';

    return sep[0];
}