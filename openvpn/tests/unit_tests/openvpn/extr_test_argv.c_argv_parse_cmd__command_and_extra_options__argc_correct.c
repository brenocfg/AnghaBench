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
struct argv {int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH1 ; 
 int /*<<< orphan*/  SCRIPT_CMD ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_parse_cmd (struct argv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
argv_parse_cmd__command_and_extra_options__argc_correct(void **state)
{
    struct argv a = argv_new();

    argv_parse_cmd(&a, SCRIPT_CMD);
    argv_printf_cat(&a, "bar baz %d %s", 42, PATH1);
    assert_int_equal(a.argc, 7);

    argv_reset(&a);
}