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
typedef  scalar_t__ u32 ;
struct controlvm_message_header {scalar_t__ id; } ;
typedef  enum controlvm_id { ____Placeholder_controlvm_id } controlvm_id ;

/* Variables and functions */
 int EINVAL ; 
 int controlvm_respond (struct controlvm_message_header*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int controlvm_responder(enum controlvm_id cmd_id,
			       struct controlvm_message_header *pending_msg_hdr,
			       int response)
{
	if (pending_msg_hdr->id != (u32)cmd_id)
		return -EINVAL;

	return controlvm_respond(pending_msg_hdr, response, NULL);
}