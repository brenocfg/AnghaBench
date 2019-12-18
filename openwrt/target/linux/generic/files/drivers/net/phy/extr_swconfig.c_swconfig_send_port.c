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
struct switch_port {int flags; int /*<<< orphan*/  id; } ;
struct swconfig_callback {struct nlattr** nest; int /*<<< orphan*/  msg; int /*<<< orphan*/  cmd; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_ATTR_PORT ; 
 int SWITCH_PORT_FLAG_TAGGED ; 
 int /*<<< orphan*/  SWITCH_PORT_ID ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 void* nla_nest_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
swconfig_send_port(struct swconfig_callback *cb, void *arg)
{
	const struct switch_port *port = arg;
	struct nlattr *p = NULL;

	if (!cb->nest[0]) {
		cb->nest[0] = nla_nest_start(cb->msg, cb->cmd);
		if (!cb->nest[0])
			return -1;
	}

	p = nla_nest_start(cb->msg, SWITCH_ATTR_PORT);
	if (!p)
		goto error;

	if (nla_put_u32(cb->msg, SWITCH_PORT_ID, port->id))
		goto nla_put_failure;
	if (port->flags & (1 << SWITCH_PORT_FLAG_TAGGED)) {
		if (nla_put_flag(cb->msg, SWITCH_PORT_FLAG_TAGGED))
			goto nla_put_failure;
	}

	nla_nest_end(cb->msg, p);
	return 0;

nla_put_failure:
		nla_nest_cancel(cb->msg, p);
error:
	nla_nest_cancel(cb->msg, cb->nest[0]);
	return -1;
}