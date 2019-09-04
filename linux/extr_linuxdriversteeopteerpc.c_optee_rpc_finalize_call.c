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
struct optee_call_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages_list (struct optee_call_ctx*) ; 

void optee_rpc_finalize_call(struct optee_call_ctx *call_ctx)
{
	free_pages_list(call_ctx);
}