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
struct TYPE_3__ {int line; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/ * json_load_file (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void very_long_file_name() {
    json_t *json;
    json_error_t error;

    json = json_load_file("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 0, &error);
    if(json)
        fail("json_load_file returned non-NULL for a nonexistent file");
    if(error.line != -1)
        fail("json_load_file returned an invalid line number");

    if (strncmp(error.source, "...aaa", 6) != 0)
        fail("error source was set incorrectly");
}