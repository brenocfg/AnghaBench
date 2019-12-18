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
typedef  int /*<<< orphan*/  uint8_t ;
struct test_buffer_list_aggregate_ctx {void* empty_buffers; void* zero_length_strings; void* one_two_three; void* empty; } ;

/* Variables and functions */
 void* buffer_list_new (int) ; 
 int /*<<< orphan*/  buffer_list_push (void*,char*) ; 
 int /*<<< orphan*/  buffer_list_push_data (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct test_buffer_list_aggregate_ctx* calloc (int,int) ; 
 char* teststr1 ; 
 char* teststr2 ; 
 char* teststr3 ; 

__attribute__((used)) static int test_buffer_list_setup(void **state)
{
    struct test_buffer_list_aggregate_ctx *ctx  = calloc(1, sizeof(*ctx));
    ctx->empty = buffer_list_new(0);

    ctx->one_two_three = buffer_list_new(3);
    buffer_list_push(ctx->one_two_three, teststr1);
    buffer_list_push(ctx->one_two_three, teststr2);
    buffer_list_push(ctx->one_two_three, teststr3);

    ctx->zero_length_strings = buffer_list_new(2);
    buffer_list_push(ctx->zero_length_strings, "");
    buffer_list_push(ctx->zero_length_strings, "");

    ctx->empty_buffers = buffer_list_new(2);
    uint8_t data = 0;
    buffer_list_push_data(ctx->empty_buffers, &data, 0);
    buffer_list_push_data(ctx->empty_buffers, &data, 0);

    *state = ctx;
    return 0;
}