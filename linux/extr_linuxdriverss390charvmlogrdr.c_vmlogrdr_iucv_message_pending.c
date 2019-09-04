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
struct vmlogrdr_priv_t {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  receive_ready; int /*<<< orphan*/  local_interrupt_buffer; } ;
struct iucv_path {struct vmlogrdr_priv_t* private; } ;
struct iucv_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iucv_message*,int) ; 
 int /*<<< orphan*/  read_wait_queue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmlogrdr_iucv_message_pending(struct iucv_path *path,
					  struct iucv_message *msg)
{
	struct vmlogrdr_priv_t * logptr = path->private;

	/*
	 * This function is the bottom half so it should be quick.
	 * Copy the external interrupt data into our local eib and increment
	 * the usage count
	 */
	spin_lock(&logptr->priv_lock);
	memcpy(&logptr->local_interrupt_buffer, msg, sizeof(*msg));
	atomic_inc(&logptr->receive_ready);
	spin_unlock(&logptr->priv_lock);
	wake_up_interruptible(&read_wait_queue);
}