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
 scalar_t__ json_array_get (int /*<<< orphan*/ *,size_t) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_copy_array(void)
{
    const char *json_array_text = "[1, \"foo\", 3.141592, {\"foo\": \"bar\"}]";

    json_t *array, *copy;
    size_t i;

    array = json_loads(json_array_text, 0, NULL);
    if(!array)
        fail("unable to parse an array");

    copy = json_copy(array);
    if(!copy)
        fail("unable to copy an array");
    if(copy == array)
        fail("copying an array doesn't copy");
    if(!json_equal(copy, array))
        fail("copying an array produces an inequal copy");

    for(i = 0; i < json_array_size(copy); i++)
    {
        if(json_array_get(array, i) != json_array_get(copy, i))
            fail("copying an array modifies its elements");
    }

    json_decref(array);
    json_decref(copy);
}