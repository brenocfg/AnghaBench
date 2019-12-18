#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
struct TYPE_37__ {size_t refcount; } ;
typedef  TYPE_1__ json_t ;
typedef  TYPE_1__ json_auto_t ;

/* Variables and functions */
 scalar_t__ JSON_INTEGER ; 
 int /*<<< orphan*/  fail (char*) ; 
 TYPE_1__* json_boolean (int) ; 
 scalar_t__ json_boolean_value (TYPE_1__*) ; 
 int /*<<< orphan*/  json_decref (TYPE_1__*) ; 
 TYPE_1__* json_false () ; 
 TYPE_1__* json_incref (TYPE_1__*) ; 
 TYPE_1__* json_integer (int) ; 
 scalar_t__ json_integer_set (TYPE_1__*,int) ; 
 int json_integer_value (TYPE_1__*) ; 
 scalar_t__ json_is_array (TYPE_1__*) ; 
 scalar_t__ json_is_boolean (TYPE_1__*) ; 
 scalar_t__ json_is_false (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_integer (TYPE_1__*) ; 
 scalar_t__ json_is_null (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_number (TYPE_1__*) ; 
 scalar_t__ json_is_object (TYPE_1__*) ; 
 scalar_t__ json_is_real (TYPE_1__*) ; 
 scalar_t__ json_is_string (TYPE_1__*) ; 
 scalar_t__ json_is_true (TYPE_1__*) ; 
 TYPE_1__* json_null () ; 
 double json_number_value (TYPE_1__*) ; 
 TYPE_1__* json_real (double) ; 
 scalar_t__ json_real_set (TYPE_1__*,double) ; 
 double json_real_value (TYPE_1__*) ; 
 TYPE_1__* json_string (char*) ; 
 int json_string_length (TYPE_1__*) ; 
 TYPE_1__* json_string_nocheck (char*) ; 
 scalar_t__ json_string_set (TYPE_1__*,char*) ; 
 scalar_t__ json_string_set_nocheck (TYPE_1__*,char*) ; 
 scalar_t__ json_string_setn (TYPE_1__*,char*,int) ; 
 scalar_t__ json_string_setn_nocheck (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  json_string_value (TYPE_1__*) ; 
 TYPE_1__* json_true () ; 
 scalar_t__ json_typeof (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void run_tests()
{
    json_t *value;

    value = json_boolean(1);
    if(!json_is_true(value))
        fail("json_boolean(1) failed");
    json_decref(value);

    value = json_boolean(-123);
    if(!json_is_true(value))
        fail("json_boolean(-123) failed");
    json_decref(value);

    value = json_boolean(0);
    if(!json_is_false(value))
        fail("json_boolean(0) failed");
    if(json_boolean_value(value) != 0)
        fail("json_boolean_value failed");
    json_decref(value);


    value = json_integer(1);
    if(json_typeof(value) != JSON_INTEGER)
        fail("json_typeof failed");

    if(json_is_object(value))
        fail("json_is_object failed");

    if(json_is_array(value))
        fail("json_is_array failed");

    if(json_is_string(value))
        fail("json_is_string failed");

    if(!json_is_integer(value))
        fail("json_is_integer failed");

    if(json_is_real(value))
        fail("json_is_real failed");

    if(!json_is_number(value))
        fail("json_is_number failed");

    if(json_is_true(value))
        fail("json_is_true failed");

    if(json_is_false(value))
        fail("json_is_false failed");

    if(json_is_boolean(value))
        fail("json_is_boolean failed");

    if(json_is_null(value))
        fail("json_is_null failed");

    json_decref(value);


    value = json_string("foo");
    if(!value)
        fail("json_string failed");
    if(strcmp(json_string_value(value), "foo"))
        fail("invalid string value");
    if (json_string_length(value) != 3)
        fail("invalid string length");

    if(json_string_set(value, "barr"))
        fail("json_string_set failed");
    if(strcmp(json_string_value(value), "barr"))
        fail("invalid string value");
    if (json_string_length(value) != 4)
        fail("invalid string length");

    if(json_string_setn(value, "hi\0ho", 5))
        fail("json_string_set failed");
    if(memcmp(json_string_value(value), "hi\0ho\0", 6))
        fail("invalid string value");
    if (json_string_length(value) != 5)
        fail("invalid string length");

    json_decref(value);

    value = json_string(NULL);
    if(value)
        fail("json_string(NULL) failed");

    /* invalid UTF-8  */
    value = json_string("a\xefz");
    if(value)
        fail("json_string(<invalid utf-8>) failed");

    value = json_string_nocheck("foo");
    if(!value)
        fail("json_string_nocheck failed");
    if(strcmp(json_string_value(value), "foo"))
        fail("invalid string value");
    if (json_string_length(value) != 3)
        fail("invalid string length");

    if(json_string_set_nocheck(value, "barr"))
        fail("json_string_set_nocheck failed");
    if(strcmp(json_string_value(value), "barr"))
        fail("invalid string value");
    if (json_string_length(value) != 4)
        fail("invalid string length");

    if(json_string_setn_nocheck(value, "hi\0ho", 5))
        fail("json_string_set failed");
    if(memcmp(json_string_value(value), "hi\0ho\0", 6))
        fail("invalid string value");
    if (json_string_length(value) != 5)
        fail("invalid string length");

    json_decref(value);

    /* invalid UTF-8 */
    value = json_string_nocheck("qu\xff");
    if(!value)
        fail("json_string_nocheck failed");
    if(strcmp(json_string_value(value), "qu\xff"))
        fail("invalid string value");
    if (json_string_length(value) != 3)
        fail("invalid string length");

    if(json_string_set_nocheck(value, "\xfd\xfe\xff"))
        fail("json_string_set_nocheck failed");
    if(strcmp(json_string_value(value), "\xfd\xfe\xff"))
        fail("invalid string value");
    if (json_string_length(value) != 3)
        fail("invalid string length");

    json_decref(value);


    value = json_integer(123);
    if(!value)
        fail("json_integer failed");
    if(json_integer_value(value) != 123)
        fail("invalid integer value");
    if(json_number_value(value) != 123.0)
        fail("invalid number value");

    if(json_integer_set(value, 321))
        fail("json_integer_set failed");
    if(json_integer_value(value) != 321)
        fail("invalid integer value");
    if(json_number_value(value) != 321.0)
        fail("invalid number value");

    json_decref(value);

    value = json_real(123.123);
    if(!value)
        fail("json_real failed");
    if(json_real_value(value) != 123.123)
        fail("invalid integer value");
    if(json_number_value(value) != 123.123)
        fail("invalid number value");

    if(json_real_set(value, 321.321))
        fail("json_real_set failed");
    if(json_real_value(value) != 321.321)
        fail("invalid real value");
    if(json_number_value(value) != 321.321)
        fail("invalid number value");

    json_decref(value);

    value = json_true();
    if(!value)
        fail("json_true failed");
    json_decref(value);

    value = json_false();
    if(!value)
        fail("json_false failed");
    json_decref(value);

    value = json_null();
    if(!value)
        fail("json_null failed");
    json_decref(value);

    /* Test reference counting on singletons (true, false, null) */
    value = json_true();
    if(value->refcount != (size_t)-1)
      fail("refcounting true works incorrectly");
    json_decref(value);
    if(value->refcount != (size_t)-1)
      fail("refcounting true works incorrectly");
    json_incref(value);
    if(value->refcount != (size_t)-1)
      fail("refcounting true works incorrectly");

    value = json_false();
    if(value->refcount != (size_t)-1)
      fail("refcounting false works incorrectly");
    json_decref(value);
    if(value->refcount != (size_t)-1)
      fail("refcounting false works incorrectly");
    json_incref(value);
    if(value->refcount != (size_t)-1)
      fail("refcounting false works incorrectly");

    value = json_null();
    if(value->refcount != (size_t)-1)
      fail("refcounting null works incorrectly");
    json_decref(value);
    if(value->refcount != (size_t)-1)
      fail("refcounting null works incorrectly");
    json_incref(value);
    if(value->refcount != (size_t)-1)
      fail("refcounting null works incorrectly");

#ifdef json_auto_t
    value = json_string("foo");
    {
        json_auto_t *test = json_incref(value);
        /* Use test so GCC doesn't complain it is unused. */
        if(!json_is_string(test))
            fail("value type check failed");
    }
    if(value->refcount != 1)
	fail("automatic decrement failed");
    json_decref(value);
#endif
}