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
struct test_buffer_list_aggregate_ctx {TYPE_1__* one_two_three; } ;
struct buffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_buf_equals_str (struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  buffer_list_aggregate_separator (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct buffer* buffer_list_peek (TYPE_1__*) ; 
 int /*<<< orphan*/  testsep ; 
 int /*<<< orphan*/  teststr1 ; 

__attribute__((used)) static void
test_buffer_list_aggregate_separator_noop(void **state)
{
    struct test_buffer_list_aggregate_ctx *ctx = *state;

    /* With a max length of 2, no aggregation should take place */
    buffer_list_aggregate_separator(ctx->one_two_three, 2, testsep);
    assert_int_equal(ctx->one_two_three->size, 3);
    struct buffer *buf = buffer_list_peek(ctx->one_two_three);
    assert_buf_equals_str(buf, teststr1);
}