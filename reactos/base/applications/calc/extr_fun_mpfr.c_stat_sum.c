#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mf; } ;
struct TYPE_5__ {scalar_t__ next; TYPE_1__ num; } ;
typedef  TYPE_2__ statistic_t ;
typedef  int /*<<< orphan*/  mpfr_t ;
struct TYPE_6__ {TYPE_2__* stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPFR_DEFAULT_RND ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  mpfr_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpfr_set_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stat_sum(mpfr_t sum)
{
    statistic_t *p = calc.stat;

    mpfr_set_ui(sum, 0, MPFR_DEFAULT_RND);
    while (p != NULL) {
        mpfr_add(sum, sum, p->num.mf, MPFR_DEFAULT_RND);
        p = (statistic_t *)(p->next);
    }
}