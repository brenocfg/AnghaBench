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
struct work_struct {int dummy; } ;
struct perf_peer {TYPE_2__* perf; int /*<<< orphan*/  sts; int /*<<< orphan*/  inbuf_xlat; int /*<<< orphan*/  outbuf_size; } ;
struct TYPE_4__ {TYPE_1__* ntb; struct perf_peer* test_peer; int /*<<< orphan*/  busy_flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_CMD_CLEAR ; 
 int /*<<< orphan*/  PERF_CMD_RSIZE ; 
 int /*<<< orphan*/  PERF_CMD_RXLAT ; 
 int /*<<< orphan*/  PERF_CMD_SSIZE ; 
 int /*<<< orphan*/  PERF_CMD_SXLAT ; 
 int /*<<< orphan*/  PERF_STS_DONE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perf_cmd_send (struct perf_peer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_free_inbuf (struct perf_peer*) ; 
 int /*<<< orphan*/  perf_free_outbuf (struct perf_peer*) ; 
 int /*<<< orphan*/  perf_setup_inbuf (struct perf_peer*) ; 
 int /*<<< orphan*/  perf_setup_outbuf (struct perf_peer*) ; 
 int /*<<< orphan*/  perf_terminate_test (TYPE_2__*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct perf_peer* to_peer_service (struct work_struct*) ; 

__attribute__((used)) static void perf_service_work(struct work_struct *work)
{
	struct perf_peer *peer = to_peer_service(work);

	if (test_and_clear_bit(PERF_CMD_SSIZE, &peer->sts))
		perf_cmd_send(peer, PERF_CMD_SSIZE, peer->outbuf_size);

	if (test_and_clear_bit(PERF_CMD_RSIZE, &peer->sts))
		perf_setup_inbuf(peer);

	if (test_and_clear_bit(PERF_CMD_SXLAT, &peer->sts))
		perf_cmd_send(peer, PERF_CMD_SXLAT, peer->inbuf_xlat);

	if (test_and_clear_bit(PERF_CMD_RXLAT, &peer->sts))
		perf_setup_outbuf(peer);

	if (test_and_clear_bit(PERF_CMD_CLEAR, &peer->sts)) {
		clear_bit(PERF_STS_DONE, &peer->sts);
		if (test_bit(0, &peer->perf->busy_flag) &&
		    peer == peer->perf->test_peer) {
			dev_warn(&peer->perf->ntb->dev,
				"Freeing while test on-fly\n");
			perf_terminate_test(peer->perf);
		}
		perf_free_outbuf(peer);
		perf_free_inbuf(peer);
	}
}