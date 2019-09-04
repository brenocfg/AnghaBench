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
 int /*<<< orphan*/  JSON_PRESERVE_ORDER ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (int) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_del (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void test_preserve_order()
{
    json_t *object;
    char *result;

    const char *expected = "{\"foobar\": 1, \"bazquux\": 6, \"lorem ipsum\": 3, \"sit amet\": 5, \"helicopter\": 7}";

    object = json_object();

    json_object_set_new(object, "foobar", json_integer(1));
    json_object_set_new(object, "bazquux", json_integer(2));
    json_object_set_new(object, "lorem ipsum", json_integer(3));
    json_object_set_new(object, "dolor", json_integer(4));
    json_object_set_new(object, "sit amet", json_integer(5));

    /* changing a value should preserve the order */
    json_object_set_new(object, "bazquux", json_integer(6));

    /* deletion shouldn't change the order of others */
    json_object_del(object, "dolor");

    /* add a new item just to make sure */
    json_object_set_new(object, "helicopter", json_integer(7));

    result = json_dumps(object, JSON_PRESERVE_ORDER);

    if(strcmp(expected, result) != 0) {
        fprintf(stderr, "%s != %s", expected, result);
        fail("JSON_PRESERVE_ORDER doesn't work");
    }

    free(result);
    json_decref(object);
}