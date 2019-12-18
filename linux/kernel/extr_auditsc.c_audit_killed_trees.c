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
struct list_head {int dummy; } ;
struct audit_context {struct list_head killed_trees; int /*<<< orphan*/  in_syscall; } ;

/* Variables and functions */
 struct audit_context* audit_context () ; 
 scalar_t__ likely (int) ; 

struct list_head *audit_killed_trees(void)
{
	struct audit_context *ctx = audit_context();
	if (likely(!ctx || !ctx->in_syscall))
		return NULL;
	return &ctx->killed_trees;
}