#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sThousand; void* sThousand_len; int /*<<< orphan*/  sDecimal; void* sDecimal_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_SDECIMAL ; 
 int /*<<< orphan*/  LOCALE_STHOUSAND ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _tcslen (int /*<<< orphan*/ ) ; 
 TYPE_1__ calc ; 

__attribute__((used)) static void UpdateNumberIntl(void)
{
    /* Get current user defaults */
    if (!GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, calc.sDecimal, SIZEOF(calc.sDecimal)))
        _tcscpy(calc.sDecimal, _T("."));

    if (!GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, calc.sThousand, SIZEOF(calc.sThousand)))
        _tcscpy(calc.sThousand, _T(","));

    /* get the string lengths */
    calc.sDecimal_len = _tcslen(calc.sDecimal);
    calc.sThousand_len = _tcslen(calc.sThousand);
}