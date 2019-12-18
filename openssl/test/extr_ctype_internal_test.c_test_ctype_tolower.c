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
struct TYPE_2__ {int /*<<< orphan*/  l; int /*<<< orphan*/  u; } ;

/* Variables and functions */
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* case_change ; 
 int /*<<< orphan*/  ossl_tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_ctype_tolower(int n)
{
    return TEST_int_eq(ossl_tolower(case_change[n].u), case_change[n].l)
           && TEST_int_eq(ossl_tolower(case_change[n].l), case_change[n].l);
}