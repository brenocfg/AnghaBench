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
struct ecryptfs_msg_ctx {scalar_t__ counter; int /*<<< orphan*/  state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_MSG_CTX_STATE_PENDING ; 
 scalar_t__ ecryptfs_msg_counter ; 
 int /*<<< orphan*/  ecryptfs_msg_ctx_alloc_list ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecryptfs_msg_ctx_free_to_alloc(struct ecryptfs_msg_ctx *msg_ctx)
{
	list_move(&msg_ctx->node, &ecryptfs_msg_ctx_alloc_list);
	msg_ctx->state = ECRYPTFS_MSG_CTX_STATE_PENDING;
	msg_ctx->counter = ++ecryptfs_msg_counter;
}