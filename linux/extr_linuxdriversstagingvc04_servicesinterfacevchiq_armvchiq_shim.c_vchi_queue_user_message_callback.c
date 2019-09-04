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
struct vchi_queue_user_message_context {scalar_t__ data; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EFAULT ; 
 scalar_t__ copy_from_user (void*,scalar_t__,size_t) ; 

__attribute__((used)) static ssize_t
vchi_queue_user_message_callback(void *context,
				 void *dest,
				 size_t offset,
				 size_t maxsize)
{
	struct vchi_queue_user_message_context *copycontext = context;

	if (copy_from_user(dest, copycontext->data + offset, maxsize))
		return -EFAULT;

	return maxsize;
}