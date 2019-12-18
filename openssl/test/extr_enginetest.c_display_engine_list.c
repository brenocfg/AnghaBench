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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_first () ; 
 int /*<<< orphan*/  ENGINE_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void display_engine_list(void)
{
    ENGINE *h;
    int loop;

    loop = 0;
    for (h = ENGINE_get_first(); h != NULL; h = ENGINE_get_next(h)) {
        TEST_info("#%d: id = \"%s\", name = \"%s\"",
               loop++, ENGINE_get_id(h), ENGINE_get_name(h));
    }

    /*
     * ENGINE_get_first() increases the struct_ref counter, so we must call
     * ENGINE_free() to decrease it again
     */
    ENGINE_free(h);
}