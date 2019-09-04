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
struct perf_peer {int /*<<< orphan*/  sts; int /*<<< orphan*/  outbuf_size; int /*<<< orphan*/  outbuf_xlat; int /*<<< orphan*/  gidx; int /*<<< orphan*/  pidx; struct perf_ctx* perf; } ;
struct perf_ctx {TYPE_1__* ntb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_STS_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ntb_peer_mw_set_trans (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_setup_outbuf(struct perf_peer *peer)
{
	struct perf_ctx *perf = peer->perf;
	int ret;

	/* Outbuf size can be unaligned due to custom max_mw_size */
	ret = ntb_peer_mw_set_trans(perf->ntb, peer->pidx, peer->gidx,
				    peer->outbuf_xlat, peer->outbuf_size);
	if (ret) {
		dev_err(&perf->ntb->dev, "Failed to set outbuf translation\n");
		return ret;
	}

	/* Initialization is finally done */
	set_bit(PERF_STS_DONE, &peer->sts);

	return 0;
}