#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tcs_cmd {int dummy; } ;
struct TYPE_2__ {int state; int num_cmds; int /*<<< orphan*/  cmds; } ;
struct rpmh_request {TYPE_1__ msg; int /*<<< orphan*/  cmd; } ;
typedef  enum rpmh_state { ____Placeholder_rpmh_state } rpmh_state ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_RPMH_PAYLOAD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct tcs_cmd const*,int) ; 

__attribute__((used)) static int __fill_rpmh_msg(struct rpmh_request *req, enum rpmh_state state,
		const struct tcs_cmd *cmd, u32 n)
{
	if (!cmd || !n || n > MAX_RPMH_PAYLOAD)
		return -EINVAL;

	memcpy(req->cmd, cmd, n * sizeof(*cmd));

	req->msg.state = state;
	req->msg.cmds = req->cmd;
	req->msg.num_cmds = n;

	return 0;
}