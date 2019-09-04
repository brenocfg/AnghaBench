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
struct TYPE_3__ {int /*<<< orphan*/  p; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ pw ;

/* Variables and functions */
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dofptest (int,int /*<<< orphan*/ ,double const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ justprint ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* pw_params ; 

__attribute__((used)) static int test_fp(int i)
{
    int t = 0, r;
    const double frac = 2.0 / 3.0;
    const pw *pwp = &pw_params[i];

    if (justprint)
        printf("    {\n");
    r = TEST_true(dofptest(i, t++, 0.0, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, 0.67, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, frac, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, frac / 1000, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, frac / 10000, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, 6.0 + frac, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, 66.0 + frac, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, 666.0 + frac, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, 6666.0 + frac, pwp->w, pwp->p))
        && TEST_true(dofptest(i, t++, 66666.0 + frac, pwp->w, pwp->p));
    if (justprint)
        printf("    },\n");
    return r;
}