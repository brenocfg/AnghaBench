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
struct argv {int /*<<< orphan*/ * argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH1 ; 
 struct argv argv_insert_head (struct argv*,int /*<<< orphan*/ ) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
argv_insert_head__empty_argv__head_only(void **state)
{
    struct argv a = argv_new();
    struct argv b;

    b = argv_insert_head(&a, PATH1);
    assert_int_equal(b.argc, 1);
    assert_string_equal(b.argv[0], PATH1);
    argv_reset(&b);

    argv_reset(&a);
}