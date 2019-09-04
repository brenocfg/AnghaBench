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
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_DISABLE_EOF_CHECK ; 
 int /*<<< orphan*/  check_error (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_eof_check()
{
    json_error_t error;
    json_t *json;

    const char *text = "{\"foo\": 1} garbage";

    if(json_loads(text, 0, &error))
        fail("json_loads did not detect garbage after JSON text");
    check_error("end of file expected near 'garbage'", "<string>", 1, 18, 18);

    json = json_loads(text, JSON_DISABLE_EOF_CHECK, &error);
    if(!json)
        fail("json_loads failed with JSON_DISABLE_EOF_CHECK");

    json_decref(json);
}