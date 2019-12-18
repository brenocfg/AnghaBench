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
struct test_buffer_list_aggregate_ctx {struct buffer_list* zero_length_strings; } ;
struct buffer_list {int /*<<< orphan*/  size; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_buf_equals_str (struct buffer*,char*) ; 
 int /*<<< orphan*/  assert_int_equal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  buffer_list_aggregate_separator (struct buffer_list*,int,int /*<<< orphan*/ ) ; 
 struct buffer* buffer_list_peek (struct buffer_list*) ; 
 int /*<<< orphan*/  testnosep ; 

__attribute__((used)) static void
test_buffer_list_aggregate_separator_zerolen(void **state)
{
    struct test_buffer_list_aggregate_ctx *ctx = *state;
    struct buffer_list *bl_zerolen = ctx->zero_length_strings;

    /* Aggregate all */
    buffer_list_aggregate_separator(bl_zerolen, 1<<16, testnosep);
    assert_int_equal(bl_zerolen->size, 1);
    struct buffer *buf = buffer_list_peek(bl_zerolen);
    assert_buf_equals_str(buf, "");
}