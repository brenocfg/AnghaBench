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
struct my_sink {int off; char* buf; int /*<<< orphan*/  cap; } ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int json_dump_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct my_sink*,int /*<<< orphan*/ ) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_writer ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void run_tests()
{
    struct my_sink s;
    json_t *json;
    const char str[] = "[\"A\", {\"B\": \"C\", \"e\": false}, 1, null, \"foo\"]";
    char *dumped_to_string;

    json = json_loads(str, 0, NULL);
    if(!json) {
        fail("json_loads failed");
    }

    dumped_to_string = json_dumps(json, 0);
    if (!dumped_to_string) {
        json_decref(json);
        fail("json_dumps failed");
    }

    s.off = 0;
    s.cap = strlen(dumped_to_string);
    s.buf = malloc(s.cap);
    if (!s.buf) {
        json_decref(json);
        free(dumped_to_string);
        fail("malloc failed");
    }

    if (json_dump_callback(json, my_writer, &s, 0) == -1) {
        json_decref(json);
        free(dumped_to_string);
        free(s.buf);
        fail("json_dump_callback failed on an exact-length sink buffer");
    }

    if (strncmp(dumped_to_string, s.buf, s.off) != 0) {
        json_decref(json);
        free(dumped_to_string);
        free(s.buf);
        fail("json_dump_callback and json_dumps did not produce identical output");
    }

    s.off = 1;
    if (json_dump_callback(json, my_writer, &s, 0) != -1) {
        json_decref(json);
        free(dumped_to_string);
        free(s.buf);
        fail("json_dump_callback succeeded on a short buffer when it should have failed");
    }

    json_decref(json);
    free(dumped_to_string);
    free(s.buf);
}