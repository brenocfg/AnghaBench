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
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_equal_complex()
{
    json_t *value1, *value2;

    const char *complex_json =
"{"
"    \"integer\": 1, "
"    \"real\": 3.141592, "
"    \"string\": \"foobar\", "
"    \"true\": true, "
"    \"object\": {"
"        \"array-in-object\": [1,true,\"foo\",{}],"
"        \"object-in-object\": {\"foo\": \"bar\"}"
"    },"
"    \"array\": [\"foo\", false, null, 1.234]"
"}";

    value1 = json_loads(complex_json, 0, NULL);
    value2 = json_loads(complex_json, 0, NULL);
    if(!value1 || !value2)
        fail("unable to parse JSON");
    if(!json_equal(value1, value2))
        fail("json_equal fails for two inequal strings");

    json_decref(value1);
    json_decref(value2);

    /* TODO: There's no negative test case here */
}