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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 double INFINITY ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_real (double) ; 
 int json_real_set (int /*<<< orphan*/ *,double) ; 
 double json_real_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_inifity()
{
    json_t *real = json_real(INFINITY);
    if (real != NULL)
       fail("could construct a real from Inf");

    real = json_real(1.0);
    if (json_real_set(real, INFINITY) != -1)
	    fail("could set a real to Inf");

    if (json_real_value(real) != 1.0)
       fail("real value changed unexpectedly");

    json_decref(real);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}