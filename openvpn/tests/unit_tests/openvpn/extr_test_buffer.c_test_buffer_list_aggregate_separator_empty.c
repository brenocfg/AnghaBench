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
struct test_buffer_list_aggregate_ctx {TYPE_1__* empty; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_list_aggregate_separator (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testsep ; 

__attribute__((used)) static void
test_buffer_list_aggregate_separator_empty(void **state)
{
    struct test_buffer_list_aggregate_ctx *ctx = *state;

    /* aggregating an empty buffer list results in an empty buffer list */
    buffer_list_aggregate_separator(ctx->empty, 3, testsep);
    assert_null(ctx->empty->head);
}