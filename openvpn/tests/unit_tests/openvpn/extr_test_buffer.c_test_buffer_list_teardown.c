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
struct test_buffer_list_aggregate_ctx {int /*<<< orphan*/  empty_buffers; int /*<<< orphan*/  zero_length_strings; int /*<<< orphan*/  one_two_three; int /*<<< orphan*/  empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct test_buffer_list_aggregate_ctx*) ; 

__attribute__((used)) static int test_buffer_list_teardown(void **state)
{
    struct test_buffer_list_aggregate_ctx *ctx = *state;

    buffer_list_free(ctx->empty);
    buffer_list_free(ctx->one_two_three);
    buffer_list_free(ctx->zero_length_strings);
    buffer_list_free(ctx->empty_buffers);
    free(ctx);
    return 0;
}