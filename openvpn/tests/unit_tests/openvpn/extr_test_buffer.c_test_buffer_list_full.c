#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct test_buffer_list_aggregate_ctx {TYPE_1__* one_two_three; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  buffer_list_push (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teststr4 ; 

__attribute__((used)) static void
test_buffer_list_full(void **state)
{
    struct test_buffer_list_aggregate_ctx *ctx = *state;

    /* list full */
    assert_int_equal(ctx->one_two_three->size, 3);
    buffer_list_push(ctx->one_two_three, teststr4);
    assert_int_equal(ctx->one_two_three->size, 3);
}