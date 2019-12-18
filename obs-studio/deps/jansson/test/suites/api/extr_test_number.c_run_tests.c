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
typedef  int json_int_t ;

/* Variables and functions */
 double NAN ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_integer (int) ; 
 int json_integer_value (int /*<<< orphan*/ *) ; 
 double json_number_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_real (double) ; 
 int json_real_set (int /*<<< orphan*/ *,double) ; 
 double json_real_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_inifity () ; 

__attribute__((used)) static void run_tests()
{
    json_t *integer, *real;
    json_int_t i;
    double d;

    integer = json_integer(5);
    real = json_real(100.1);

    if(!integer)
        fail("unable to create integer");
    if(!real)
        fail("unable to create real");

    i = json_integer_value(integer);
    if(i != 5)
        fail("wrong integer value");

    d = json_real_value(real);
    if(d != 100.1)
        fail("wrong real value");

    d = json_number_value(integer);
    if(d != 5.0)
        fail("wrong number value");
    d = json_number_value(real);
    if(d != 100.1)
        fail("wrong number value");

    json_decref(integer);
    json_decref(real);

#ifdef NAN
    real = json_real(NAN);
    if(real != NULL)
        fail("could construct a real from NaN");

    real = json_real(1.0);
    if(json_real_set(real, NAN) != -1)
        fail("could set a real to NaN");

    if(json_real_value(real) != 1.0)
        fail("real value changed unexpectedly");

    json_decref(real);
#endif

#ifdef INFINITY
    test_inifity();
#endif
}