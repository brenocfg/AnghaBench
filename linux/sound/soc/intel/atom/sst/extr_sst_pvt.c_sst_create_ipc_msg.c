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
struct ipc_post {int is_large; int /*<<< orphan*/ * mailbox_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SST_MAILBOX_SIZE ; 
 int /*<<< orphan*/  kfree (struct ipc_post*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

int sst_create_ipc_msg(struct ipc_post **arg, bool large)
{
	struct ipc_post *msg;

	msg = kzalloc(sizeof(*msg), GFP_ATOMIC);
	if (!msg)
		return -ENOMEM;
	if (large) {
		msg->mailbox_data = kzalloc(SST_MAILBOX_SIZE, GFP_ATOMIC);
		if (!msg->mailbox_data) {
			kfree(msg);
			return -ENOMEM;
		}
	} else {
		msg->mailbox_data = NULL;
	}
	msg->is_large = large;
	*arg = msg;
	return 0;
}