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
 int json_dump_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static void dump_file()
{
    json_t *json;
    int result;

    result = json_dump_file(NULL, "", 0);
    if (result != -1)
        fail("json_dump_file succeeded with invalid args");

    json = json_object();
    result = json_dump_file(json, "json_dump_file.json", 0);
    if (result != 0)
        fail("json_dump_file failed");

    json_decref(json);
    remove("json_dump_file.json");
}