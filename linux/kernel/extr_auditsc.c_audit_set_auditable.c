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
struct audit_context {int prio; int /*<<< orphan*/  current_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_RECORD_CONTEXT ; 

__attribute__((used)) static void audit_set_auditable(struct audit_context *ctx)
{
	if (!ctx->prio) {
		ctx->prio = 1;
		ctx->current_state = AUDIT_RECORD_CONTEXT;
	}
}