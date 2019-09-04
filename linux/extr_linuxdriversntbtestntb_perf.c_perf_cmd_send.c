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
typedef  int /*<<< orphan*/  u64 ;
struct perf_peer {struct perf_ctx* perf; } ;
struct perf_ctx {int (* cmd_send ) (struct perf_peer*,int,int /*<<< orphan*/ ) ;TYPE_1__* ntb; } ;
typedef  enum perf_cmd { ____Placeholder_perf_cmd } perf_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int PERF_CMD_SSIZE ; 
 int PERF_CMD_SXLAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct perf_peer*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_cmd_send(struct perf_peer *peer, enum perf_cmd cmd, u64 data)
{
	struct perf_ctx *perf = peer->perf;

	if (cmd == PERF_CMD_SSIZE || cmd == PERF_CMD_SXLAT)
		return perf->cmd_send(peer, cmd, data);

	dev_err(&perf->ntb->dev, "Send invalid command\n");
	return -EINVAL;
}