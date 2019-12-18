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
struct argv {int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH1 ; 
 int /*<<< orphan*/  PATH2 ; 
 struct argv argv_insert_head (struct argv*,int /*<<< orphan*/ ) ; 
 struct argv argv_new () ; 
 int /*<<< orphan*/  argv_printf (struct argv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_reset (struct argv*) ; 
 int /*<<< orphan*/  assert_int_equal (int,int) ; 
 int /*<<< orphan*/  assert_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
argv_insert_head__non_empty_argv__head_added(void **state)
{
    struct argv a = argv_new();
    struct argv b;
    int i;

    argv_printf(&a, "%s", PATH2);
    b = argv_insert_head(&a, PATH1);
    assert_int_equal(b.argc, a.argc + 1);
    for (i = 0; i < b.argc; i++) {
        if (i == 0)
        {
            assert_string_equal(b.argv[i], PATH1);
        }
        else
        {
            assert_string_equal(b.argv[i], a.argv[i - 1]);
        }
    }
    argv_reset(&b);

    argv_reset(&a);
}