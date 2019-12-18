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
struct tipc_nl_compat_msg {int /*<<< orphan*/  rep; scalar_t__ req_type; int /*<<< orphan*/  req; int /*<<< orphan*/  req_size; } ;
struct tipc_nl_compat_cmd_doit {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TLV_CHECK_TYPE (int /*<<< orphan*/ ,scalar_t__) ; 
 int __tipc_nl_compat_doit (struct tipc_nl_compat_cmd_doit*,struct tipc_nl_compat_msg*) ; 
 int /*<<< orphan*/  tipc_tlv_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_nl_compat_doit(struct tipc_nl_compat_cmd_doit *cmd,
			       struct tipc_nl_compat_msg *msg)
{
	int err;

	if (msg->req_type && (!msg->req_size ||
			      !TLV_CHECK_TYPE(msg->req, msg->req_type)))
		return -EINVAL;

	err = __tipc_nl_compat_doit(cmd, msg);
	if (err)
		return err;

	/* The legacy API considered an empty message a success message */
	msg->rep = tipc_tlv_alloc(0);
	if (!msg->rep)
		return -ENOMEM;

	return 0;
}