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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ecryptfs_msg_ctx {int msg_size; int /*<<< orphan*/  mux; int /*<<< orphan*/  daemon_out_list; struct ecryptfs_message* msg; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct ecryptfs_message {size_t data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  index; } ;
struct ecryptfs_daemon {int /*<<< orphan*/  mux; int /*<<< orphan*/  wait; int /*<<< orphan*/  num_queued_msg_ctx; int /*<<< orphan*/  msg_ctx_out_queue; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ecryptfs_message* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int ecryptfs_send_miscdev(char *data, size_t data_size,
			  struct ecryptfs_msg_ctx *msg_ctx, u8 msg_type,
			  u16 msg_flags, struct ecryptfs_daemon *daemon)
{
	struct ecryptfs_message *msg;

	msg = kmalloc((sizeof(*msg) + data_size), GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	mutex_lock(&msg_ctx->mux);
	msg_ctx->msg = msg;
	msg_ctx->msg->index = msg_ctx->index;
	msg_ctx->msg->data_len = data_size;
	msg_ctx->type = msg_type;
	memcpy(msg_ctx->msg->data, data, data_size);
	msg_ctx->msg_size = (sizeof(*msg_ctx->msg) + data_size);
	list_add_tail(&msg_ctx->daemon_out_list, &daemon->msg_ctx_out_queue);
	mutex_unlock(&msg_ctx->mux);

	mutex_lock(&daemon->mux);
	daemon->num_queued_msg_ctx++;
	wake_up_interruptible(&daemon->wait);
	mutex_unlock(&daemon->mux);

	return 0;
}