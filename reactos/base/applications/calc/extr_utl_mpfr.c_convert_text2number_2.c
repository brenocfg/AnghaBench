#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {int base; char* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
#define  IDC_RADIO_BIN 131 
#define  IDC_RADIO_DEC 130 
#define  IDC_RADIO_HEX 129 
#define  IDC_RADIO_OCT 128 
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _alloca (int) ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  mpfr_strtofr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void convert_text2number_2(calc_number_t *a)
{
    int base;
#ifdef UNICODE
    int sz;
    char *temp;
#endif

    switch (calc.base) {
    case IDC_RADIO_HEX: base = 16; break;
    case IDC_RADIO_DEC: base = 10; break;
    case IDC_RADIO_OCT: base = 8; break;
    case IDC_RADIO_BIN: base = 2; break;
    default: return;
    }
#ifdef UNICODE
/*
 * libmpfr and libgmp accept only ascii chars.
 */
    sz = WideCharToMultiByte(CP_ACP, 0, calc.buffer, -1, NULL, 0, NULL, NULL);
    if (!sz)
        return;
    temp = (char *)_alloca(sz);
    sz = WideCharToMultiByte(CP_ACP, 0, calc.buffer, -1, temp, sz, NULL, NULL);
    mpfr_strtofr(a->mf, temp, NULL, base, MPFR_DEFAULT_RND);
#else
    mpfr_strtofr(a->mf, calc.buffer, NULL, base, MPFR_DEFAULT_RND);
#endif
}