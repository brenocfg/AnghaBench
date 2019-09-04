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
struct optee_call_ctx {scalar_t__ num_entries; int /*<<< orphan*/ * pages_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  optee_free_pages_list (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void free_pages_list(struct optee_call_ctx *call_ctx)
{
	if (call_ctx->pages_list) {
		optee_free_pages_list(call_ctx->pages_list,
				      call_ctx->num_entries);
		call_ctx->pages_list = NULL;
		call_ctx->num_entries = 0;
	}
}