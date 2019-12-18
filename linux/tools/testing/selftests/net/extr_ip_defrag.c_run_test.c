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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_sec; int tv_usec; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int FRAG_HLEN ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int MSG_LEN_MAX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfg_overlap ; 
 scalar_t__ cfg_verbose ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int frag_counter ; 
 int max_frag_len ; 
 int msg_counter ; 
 int payload_len ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int rand () ; 
 int /*<<< orphan*/  recv_validate_udp (int) ; 
 int /*<<< orphan*/  send_udp_frags (int,struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int* udp_payload ; 

__attribute__((used)) static void run_test(struct sockaddr *addr, socklen_t alen, bool ipv6)
{
	int fd_tx_raw, fd_rx_udp;
	/* Frag queue timeout is set to one second in the calling script;
	 * socket timeout should be just a bit longer to avoid tests interfering
	 * with each other.
	 */
	struct timeval tv = { .tv_sec = 1, .tv_usec = 10 };
	int idx;
	int min_frag_len = 8;

	/* Initialize the payload. */
	for (idx = 0; idx < MSG_LEN_MAX; ++idx)
		udp_payload[idx] = idx % 256;

	/* Open sockets. */
	fd_tx_raw = socket(addr->sa_family, SOCK_RAW, IPPROTO_RAW);
	if (fd_tx_raw == -1)
		error(1, errno, "socket tx_raw");

	fd_rx_udp = socket(addr->sa_family, SOCK_DGRAM, 0);
	if (fd_rx_udp == -1)
		error(1, errno, "socket rx_udp");
	if (bind(fd_rx_udp, addr, alen))
		error(1, errno, "bind");
	/* Fail fast. */
	if (setsockopt(fd_rx_udp, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
		error(1, errno, "setsockopt rcv timeout");

	for (payload_len = min_frag_len; payload_len < MSG_LEN_MAX;
			payload_len += (rand() % 4096)) {
		if (cfg_verbose)
			printf("payload_len: %d\n", payload_len);

		if (cfg_overlap) {
			/* With overlaps, one send/receive pair below takes
			 * at least one second (== timeout) to run, so there
			 * is not enough test time to run a nested loop:
			 * the full overlap test takes 20-30 seconds.
			 */
			max_frag_len = min_frag_len +
				rand() % (1500 - FRAG_HLEN - min_frag_len);
			send_udp_frags(fd_tx_raw, addr, alen, ipv6);
			recv_validate_udp(fd_rx_udp);
		} else {
			/* Without overlaps, each packet reassembly (== one
			 * send/receive pair below) takes very little time to
			 * run, so we can easily afford more thourough testing
			 * with a nested loop: the full non-overlap test takes
			 * less than one second).
			 */
			max_frag_len = min_frag_len;
			do {
				send_udp_frags(fd_tx_raw, addr, alen, ipv6);
				recv_validate_udp(fd_rx_udp);
				max_frag_len += 8 * (rand() % 8);
			} while (max_frag_len < (1500 - FRAG_HLEN) &&
				 max_frag_len <= payload_len);
		}
	}

	/* Cleanup. */
	if (close(fd_tx_raw))
		error(1, errno, "close tx_raw");
	if (close(fd_rx_udp))
		error(1, errno, "close rx_udp");

	if (cfg_verbose)
		printf("processed %d messages, %d fragments\n",
			msg_counter, frag_counter);

	fprintf(stderr, "PASS\n");
}