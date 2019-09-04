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
struct xdpsock {scalar_t__ sfd; int /*<<< orphan*/  outstanding_tx; int /*<<< orphan*/  tx; } ;
struct pollfd {scalar_t__ fd; int events; int revents; } ;
typedef  int /*<<< orphan*/  fds ;

/* Variables and functions */
 scalar_t__ BATCH_SIZE ; 
 unsigned int NUM_FRAMES ; 
 int POLLOUT ; 
 int /*<<< orphan*/  complete_tx_only (struct xdpsock*) ; 
 int /*<<< orphan*/  lassert (int) ; 
 int /*<<< orphan*/  memset (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ opt_poll ; 
 int poll (struct pollfd*,int,int) ; 
 scalar_t__ xq_enq_tx_only (int /*<<< orphan*/ *,unsigned int,scalar_t__) ; 
 scalar_t__ xq_nb_free (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void tx_only(struct xdpsock *xsk)
{
	int timeout, ret, nfds = 1;
	struct pollfd fds[nfds + 1];
	unsigned int idx = 0;

	memset(fds, 0, sizeof(fds));
	fds[0].fd = xsk->sfd;
	fds[0].events = POLLOUT;
	timeout = 1000; /* 1sn */

	for (;;) {
		if (opt_poll) {
			ret = poll(fds, nfds, timeout);
			if (ret <= 0)
				continue;

			if (fds[0].fd != xsk->sfd ||
			    !(fds[0].revents & POLLOUT))
				continue;
		}

		if (xq_nb_free(&xsk->tx, BATCH_SIZE) >= BATCH_SIZE) {
			lassert(xq_enq_tx_only(&xsk->tx, idx, BATCH_SIZE) == 0);

			xsk->outstanding_tx += BATCH_SIZE;
			idx += BATCH_SIZE;
			idx %= NUM_FRAMES;
		}

		complete_tx_only(xsk);
	}
}