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
struct sockmap_options {int iov_count; int iov_length; int rate; scalar_t__ verbose; scalar_t__ sendpage; scalar_t__ drop_expected; scalar_t__ base; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_sec; } ;
struct msg_stats {int /*<<< orphan*/  bytes_recvd; int /*<<< orphan*/  bytes_sent; TYPE_2__ start; TYPE_1__ end; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int c1 ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 float giga ; 
 scalar_t__ ktls ; 
 int msg_loop (int,int,int,int,struct msg_stats*,int,struct sockmap_options*) ; 
 int msg_loop_sendpage (int,int,int,struct msg_stats*,struct sockmap_options*) ; 
 int p1 ; 
 int p2 ; 
 scalar_t__ peek_flag ; 
 int /*<<< orphan*/  perror (char*) ; 
 float recvdBps (struct msg_stats) ; 
 float sentBps (struct msg_stats) ; 
 int sockmap_init_ktls (scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ txmsg_cork ; 
 scalar_t__ txmsg_ingress ; 
 scalar_t__ txmsg_redir ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sendmsg_test(struct sockmap_options *opt)
{
	float sent_Bps = 0, recvd_Bps = 0;
	int rx_fd, txpid, rxpid, err = 0;
	struct msg_stats s = {0};
	int iov_count = opt->iov_count;
	int iov_buf = opt->iov_length;
	int rx_status, tx_status;
	int cnt = opt->rate;

	errno = 0;

	if (opt->base)
		rx_fd = p1;
	else
		rx_fd = p2;

	if (ktls) {
		/* Redirecting into non-TLS socket which sends into a TLS
		 * socket is not a valid test. So in this case lets not
		 * enable kTLS but still run the test.
		 */
		if (!txmsg_redir || (txmsg_redir && txmsg_ingress)) {
			err = sockmap_init_ktls(opt->verbose, rx_fd);
			if (err)
				return err;
		}
		err = sockmap_init_ktls(opt->verbose, c1);
		if (err)
			return err;
	}

	rxpid = fork();
	if (rxpid == 0) {
		if (opt->drop_expected)
			exit(0);

		if (opt->sendpage)
			iov_count = 1;
		err = msg_loop(rx_fd, iov_count, iov_buf,
			       cnt, &s, false, opt);
		if (opt->verbose)
			fprintf(stderr,
				"msg_loop_rx: iov_count %i iov_buf %i cnt %i err %i\n",
				iov_count, iov_buf, cnt, err);
		if (s.end.tv_sec - s.start.tv_sec) {
			sent_Bps = sentBps(s);
			recvd_Bps = recvdBps(s);
		}
		if (opt->verbose)
			fprintf(stdout,
				"rx_sendmsg: TX: %zuB %fB/s %fGB/s RX: %zuB %fB/s %fGB/s %s\n",
				s.bytes_sent, sent_Bps, sent_Bps/giga,
				s.bytes_recvd, recvd_Bps, recvd_Bps/giga,
				peek_flag ? "(peek_msg)" : "");
		if (err && txmsg_cork)
			err = 0;
		exit(err ? 1 : 0);
	} else if (rxpid == -1) {
		perror("msg_loop_rx: ");
		return errno;
	}

	txpid = fork();
	if (txpid == 0) {
		if (opt->sendpage)
			err = msg_loop_sendpage(c1, iov_buf, cnt, &s, opt);
		else
			err = msg_loop(c1, iov_count, iov_buf,
				       cnt, &s, true, opt);

		if (err)
			fprintf(stderr,
				"msg_loop_tx: iov_count %i iov_buf %i cnt %i err %i\n",
				iov_count, iov_buf, cnt, err);
		if (s.end.tv_sec - s.start.tv_sec) {
			sent_Bps = sentBps(s);
			recvd_Bps = recvdBps(s);
		}
		if (opt->verbose)
			fprintf(stdout,
				"tx_sendmsg: TX: %zuB %fB/s %f GB/s RX: %zuB %fB/s %fGB/s\n",
				s.bytes_sent, sent_Bps, sent_Bps/giga,
				s.bytes_recvd, recvd_Bps, recvd_Bps/giga);
		exit(err ? 1 : 0);
	} else if (txpid == -1) {
		perror("msg_loop_tx: ");
		return errno;
	}

	assert(waitpid(rxpid, &rx_status, 0) == rxpid);
	assert(waitpid(txpid, &tx_status, 0) == txpid);
	if (WIFEXITED(rx_status)) {
		err = WEXITSTATUS(rx_status);
		if (err) {
			fprintf(stderr, "rx thread exited with err %d. ", err);
			goto out;
		}
	}
	if (WIFEXITED(tx_status)) {
		err = WEXITSTATUS(tx_status);
		if (err)
			fprintf(stderr, "tx thread exited with err %d. ", err);
	}
out:
	return err;
}