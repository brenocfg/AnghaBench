#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double* data; } ;
typedef  TYPE_1__ OSSL_PARAM ;

/* Variables and functions */
 TYPE_1__ OSSL_PARAM_double (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_double (TYPE_1__*,double) ; 
 scalar_t__ TEST_double_eq (double,double) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_param_real(void)
{
    double p;
    OSSL_PARAM param = OSSL_PARAM_double("r", NULL);

    param.data = &p;
    return TEST_true(OSSL_PARAM_set_double(&param, 3.14159))
           && TEST_double_eq(p, 3.14159);
}