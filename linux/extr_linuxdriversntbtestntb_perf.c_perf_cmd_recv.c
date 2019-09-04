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
typedef  void* u64 ;
struct perf_peer {void* outbuf_xlat; void* inbuf_size; } ;
struct perf_ctx {int (* cmd_recv ) (struct perf_ctx*,int*,int*,void**) ;TYPE_1__* ntb; struct perf_peer* peers; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  PERF_CMD_RSIZE ; 
 int /*<<< orphan*/  PERF_CMD_RXLAT ; 
#define  PERF_CMD_SSIZE 129 
#define  PERF_CMD_SXLAT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int perf_cmd_exec (struct perf_peer*,int /*<<< orphan*/ ) ; 
 int stub1 (struct perf_ctx*,int*,int*,void**) ; 

__attribute__((used)) static int perf_cmd_recv(struct perf_ctx *perf)
{
	struct perf_peer *peer;
	int ret, pidx, cmd;
	u64 data;

	while (!(ret = perf->cmd_recv(perf, &pidx, &cmd, &data))) {
		peer = &perf->peers[pidx];

		switch (cmd) {
		case PERF_CMD_SSIZE:
			peer->inbuf_size = data;
			return perf_cmd_exec(peer, PERF_CMD_RSIZE);
		case PERF_CMD_SXLAT:
			peer->outbuf_xlat = data;
			return perf_cmd_exec(peer, PERF_CMD_RXLAT);
		default:
			dev_err(&perf->ntb->dev, "Recv invalid command\n");
			return -EINVAL;
		}
	}

	/* Return 0 if no data left to process, otherwise an error */
	return ret == -ENODATA ? 0 : ret;
}