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
 int /*<<< orphan*/  PARAM1 ; 
 int /*<<< orphan*/  PATH1 ; 
 int /*<<< orphan*/  PATH2 ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_printf_cat (struct argv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
argv_printf_cat__multiple_spaces_in_format__parsed_as_one(void **state)
{
    struct argv a = argv_new();

    argv_printf(&a, "%s ", PATH1);
    argv_printf_cat(&a, " %s  %s", PATH2, PARAM1);
    assert_int_equal(a.argc, 3);

    argv_reset(&a);
}