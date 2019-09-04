#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mf; } ;
struct TYPE_7__ {scalar_t__ next; TYPE_1__ num; } ;
typedef  TYPE_2__ statistic_t ;
typedef  int /*<<< orphan*/  mpfr_t ;
struct TYPE_8__ {int /*<<< orphan*/  mf; } ;
typedef  TYPE_3__ calc_number_t ;
struct TYPE_9__ {scalar_t__ base; TYPE_2__* stat; int /*<<< orphan*/  hStatWnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_LIST_STAT ; 
 scalar_t__ IDC_RADIO_DEC ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 unsigned long SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ calc ; 
 int /*<<< orphan*/  mpfr_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_div_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_set_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_sqr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_sqrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_sum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpn_s_ex(calc_number_t *c, int pop_type)
{
    mpfr_t        dev;
    mpfr_t        num;
    unsigned long n = 0;
    statistic_t  *p = calc.stat;

    n = SendDlgItemMessage(calc.hStatWnd, IDC_LIST_STAT, LB_GETCOUNT, 0, 0);
    if (n < 2) {
        mpfr_set_ui(c->mf, 0, MPFR_DEFAULT_RND);
        return;
    }

    stat_sum(c->mf);
    mpfr_div_ui(c->mf, c->mf, n, MPFR_DEFAULT_RND);

    mpfr_init(dev);
    mpfr_init(num);

    mpfr_set_ui(dev, 0, MPFR_DEFAULT_RND);
    p = calc.stat;
    while (p != NULL) {
        mpfr_sub(num, p->num.mf, c->mf, MPFR_DEFAULT_RND);
        mpfr_sqr(num, num, MPFR_DEFAULT_RND);
        mpfr_add(dev, dev, num, MPFR_DEFAULT_RND);
        p = (statistic_t *)(p->next);
    }
    mpfr_div_ui(c->mf, dev, pop_type ? n-1 : n, MPFR_DEFAULT_RND);
    mpfr_sqrt(c->mf, c->mf, MPFR_DEFAULT_RND);

    if (calc.base != IDC_RADIO_DEC)
        mpfr_trunc(c->mf, c->mf);

    mpfr_clear(dev);
    mpfr_clear(num);
}