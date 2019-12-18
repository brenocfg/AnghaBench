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
struct mgmt_pending_cmd {int /*<<< orphan*/ * sk; } ;
struct cmd_lookup {int /*<<< orphan*/ * sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sk_lookup(struct mgmt_pending_cmd *cmd, void *data)
{
	struct cmd_lookup *match = data;

	if (match->sk == NULL) {
		match->sk = cmd->sk;
		sock_hold(match->sk);
	}
}