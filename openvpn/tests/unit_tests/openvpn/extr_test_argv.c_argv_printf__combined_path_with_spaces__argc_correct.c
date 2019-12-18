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
 int /*<<< orphan*/  PATH2 ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
argv_printf__combined_path_with_spaces__argc_correct(void **state)
{
    struct argv a = argv_new();

    argv_printf(&a, "%s%sc", PATH1, PATH2);
    assert_int_equal(a.argc, 1);

    argv_printf(&a, "%s%sc %d", PATH1, PATH2, 42);
    assert_int_equal(a.argc, 2);

    argv_printf(&a, "foo %s%sc %s x y", PATH2, PATH1, "foo");
    assert_int_equal(a.argc, 5);

    argv_reset(&a);
}