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
struct TYPE_5__ {scalar_t__ base; int /*<<< orphan*/  hStatWnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_LIST_STAT ; 
 scalar_t__ IDC_RADIO_DEC ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 int SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  mpfr_div_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_sum (int /*<<< orphan*/ ) ; 

void rpn_ave(calc_number_t *c)
{
    int     n;

    stat_sum(c->mf);
    n = SendDlgItemMessage(calc.hStatWnd, IDC_LIST_STAT, LB_GETCOUNT, 0, 0);

    if (n)
        mpfr_div_ui(c->mf, c->mf, n, MPFR_DEFAULT_RND);

    if (calc.base != IDC_RADIO_DEC)
        mpfr_trunc(c->mf, c->mf);
}