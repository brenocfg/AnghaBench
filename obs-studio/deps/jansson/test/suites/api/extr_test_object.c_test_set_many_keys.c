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
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_string (char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void test_set_many_keys()
{
    json_t *object, *value;
    const char *keys = "abcdefghijklmnopqrstuvwxyz";
    char buf[2];
    size_t i;

    object = json_object();
    if (!object)
        fail("unable to create object");

    value = json_string("a");
    if (!value)
        fail("unable to create string");

    buf[1] = '\0';
    for (i = 0; i < strlen(keys); i++) {
        buf[0] = keys[i];
        if (json_object_set(object, buf, value))
            fail("unable to set object key");
    }

    json_decref(object);
    json_decref(value);
}