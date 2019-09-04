#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_peer {int /*<<< orphan*/  service; TYPE_2__* perf; int /*<<< orphan*/  sts; } ;
typedef  enum perf_cmd { ____Placeholder_perf_cmd } perf_cmd ;
struct TYPE_4__ {TYPE_1__* ntb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PERF_CMD_CLEAR 132 
#define  PERF_CMD_RSIZE 131 
#define  PERF_CMD_RXLAT 130 
#define  PERF_CMD_SSIZE 129 
#define  PERF_CMD_SXLAT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_highpri_wq ; 

__attribute__((used)) static int perf_cmd_exec(struct perf_peer *peer, enum perf_cmd cmd)
{
	switch (cmd) {
	case PERF_CMD_SSIZE:
	case PERF_CMD_RSIZE:
	case PERF_CMD_SXLAT:
	case PERF_CMD_RXLAT:
	case PERF_CMD_CLEAR:
		break;
	default:
		dev_err(&peer->perf->ntb->dev, "Exec invalid command\n");
		return -EINVAL;
	}

	/* No need of memory barrier, since bit ops have invernal lock */
	set_bit(cmd, &peer->sts);

	dev_dbg(&peer->perf->ntb->dev, "CMD exec: %d\n", cmd);

	(void)queue_work(system_highpri_wq, &peer->service);

	return 0;
}