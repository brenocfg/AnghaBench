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
typedef  int /*<<< orphan*/  json_t ;
typedef  long long json_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int JSON_DECODE_ANY ; 
 int JSON_DECODE_INT_AS_REAL ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_is_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int,TYPE_1__*) ; 
 double json_real_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void decode_int_as_real()
{
    json_t *json;
    json_error_t error;

#if JSON_INTEGER_IS_LONG_LONG
    const char *imprecise;
    json_int_t expected;
#endif

    char big[311];

    json = json_loads("42", JSON_DECODE_INT_AS_REAL | JSON_DECODE_ANY, &error);
    if (!json || !json_is_real(json) || json_real_value(json) != 42.0)
        fail("json_load decode int as real failed - int");
    json_decref(json);

#if JSON_INTEGER_IS_LONG_LONG
    /* This number cannot be represented exactly by a double */
    imprecise = "9007199254740993";
    expected = 9007199254740992ll;

    json = json_loads(imprecise, JSON_DECODE_INT_AS_REAL | JSON_DECODE_ANY,
                      &error);
    if (!json || !json_is_real(json) || expected != (json_int_t)json_real_value(json))
        fail("json_load decode int as real failed - expected imprecision");
    json_decref(json);
#endif

    /* 1E309 overflows. Here we create 1E309 as a decimal number, i.e.
       1000...(309 zeroes)...0. */
    big[0] = '1';
    memset(big + 1, '0', 309);
    big[310] = '\0';

    json = json_loads(big, JSON_DECODE_INT_AS_REAL | JSON_DECODE_ANY, &error);
    if (json || strcmp(error.text, "real number overflow") != 0)
        fail("json_load decode int as real failed - expected overflow");
    json_decref(json);

}