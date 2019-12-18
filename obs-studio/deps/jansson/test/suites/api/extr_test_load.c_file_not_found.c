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
struct TYPE_3__ {int line; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/ * json_load_file (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void file_not_found()
{
    json_t *json;
    json_error_t error;
    char *pos;

    json = json_load_file("/path/to/nonexistent/file.json", 0, &error);
    if(json)
        fail("json_load_file returned non-NULL for a nonexistent file");
    if(error.line != -1)
        fail("json_load_file returned an invalid line number");

    /* The error message is locale specific, only check the beginning
       of the error message. */

    pos = strchr(error.text, ':');
    if(!pos)
        fail("json_load_file returne an invalid error message");

    *pos = '\0';

    if(strcmp(error.text, "unable to open /path/to/nonexistent/file.json") != 0)
        fail("json_load_file returned an invalid error message");
}