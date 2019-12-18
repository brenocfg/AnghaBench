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
struct the_list {int /*<<< orphan*/  member_0; } ;
struct test_ctx {int dummy; } ;
struct list_item {int member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_APPEND (int /*<<< orphan*/ ,struct the_list*,struct list_item*) ; 
 int /*<<< orphan*/  LL_CLEAR (int /*<<< orphan*/ ,struct the_list*) ; 
 int /*<<< orphan*/  LL_INSERT_AFTER (int /*<<< orphan*/ ,struct the_list*,struct list_item*,struct list_item*) ; 
 int /*<<< orphan*/  LL_INSERT_BEFORE (int /*<<< orphan*/ ,struct the_list*,struct list_item*,struct list_item*) ; 
 int /*<<< orphan*/  LL_PREPEND (int /*<<< orphan*/ ,struct the_list*,struct list_item*) ; 
 int /*<<< orphan*/  LL_REMOVE (int /*<<< orphan*/ ,struct the_list*,struct list_item*) ; 
 struct list_item* STUPID_SHIT (struct list_item*) ; 
 int /*<<< orphan*/  check_list (int,...) ; 
 int /*<<< orphan*/  check_list_empty () ; 
 int /*<<< orphan*/  list_node ; 

__attribute__((used)) static void run(struct test_ctx *ctx)
{
    struct the_list lst = {0};
    struct list_item e1 = {1};
    struct list_item e2 = {2};
    struct list_item e3 = {3};
    struct list_item e4 = {4};
    struct list_item e5 = {5};
    struct list_item e6 = {6};

#define check_list(...) \
        assert_true(do_check_list(&lst, (int[]){__VA_ARGS__}, \
                        sizeof((int[]){__VA_ARGS__}) / sizeof(int)));
#define check_list_empty() \
        assert_true(do_check_list(&lst, NULL, 0));

    check_list_empty();
    LL_APPEND(list_node, &lst, &e1);

    check_list(1);
    LL_APPEND(list_node, &lst, &e2);

    check_list(1, 2);
    LL_APPEND(list_node, &lst, &e4);

    check_list(1, 2, 4);
    LL_CLEAR(list_node, &lst);

    check_list_empty();
    LL_PREPEND(list_node, &lst, &e4);

    check_list(4);
    LL_PREPEND(list_node, &lst, &e2);

    check_list(2, 4);
    LL_PREPEND(list_node, &lst, &e1);

    check_list(1, 2, 4);
    LL_CLEAR(list_node, &lst);

    check_list_empty();
    LL_INSERT_BEFORE(list_node, &lst, (struct list_item *)NULL, &e6);

    check_list(6);
    LL_INSERT_BEFORE(list_node, &lst, (struct list_item *)NULL, &e1);

    check_list(6, 1);
    LL_INSERT_BEFORE(list_node, &lst, (struct list_item *)NULL, &e2);

    check_list(6, 1, 2);
    LL_INSERT_BEFORE(list_node, &lst, STUPID_SHIT(&e6), &e3);

    check_list(3, 6, 1, 2);
    LL_INSERT_BEFORE(list_node, &lst, STUPID_SHIT(&e6), &e5);

    check_list(3, 5, 6, 1, 2);
    LL_INSERT_BEFORE(list_node, &lst, STUPID_SHIT(&e2), &e4);

    check_list(3, 5, 6, 1, 4, 2);
    LL_REMOVE(list_node, &lst, &e6);

    check_list(3, 5, 1, 4, 2);
    LL_REMOVE(list_node, &lst, &e3);

    check_list(5, 1, 4, 2);
    LL_REMOVE(list_node, &lst, &e2);

    check_list(5, 1, 4);
    LL_REMOVE(list_node, &lst, &e4);

    check_list(5, 1);
    LL_REMOVE(list_node, &lst, &e5);

    check_list(1);
    LL_REMOVE(list_node, &lst, &e1);

    check_list_empty();
    LL_APPEND(list_node, &lst, &e2);

    check_list(2);
    LL_REMOVE(list_node, &lst, &e2);

    check_list_empty();
    LL_INSERT_AFTER(list_node, &lst, (struct list_item *)NULL, &e1);

    check_list(1);
    LL_INSERT_AFTER(list_node, &lst, (struct list_item *)NULL, &e2);

    check_list(2, 1);
    LL_INSERT_AFTER(list_node, &lst, (struct list_item *)NULL, &e3);

    check_list(3, 2, 1);
    LL_INSERT_AFTER(list_node, &lst, STUPID_SHIT(&e3), &e4);

    check_list(3, 4, 2, 1);
    LL_INSERT_AFTER(list_node, &lst, STUPID_SHIT(&e4), &e5);

    check_list(3, 4, 5, 2, 1);
    LL_INSERT_AFTER(list_node, &lst, STUPID_SHIT(&e1), &e6);

    check_list(3, 4, 5, 2, 1, 6);
}