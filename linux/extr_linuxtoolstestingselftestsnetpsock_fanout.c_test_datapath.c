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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_CHAR_1 ; 
 scalar_t__ PACKET_FANOUT_CBPF ; 
 scalar_t__ PACKET_FANOUT_EBPF ; 
 scalar_t__ PORT_BASE ; 
 int RING_NUM_FRAMES ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getpagesize () ; 
 scalar_t__ munmap (char*,int) ; 
 int /*<<< orphan*/  pair_udp_open (int*,scalar_t__) ; 
 int /*<<< orphan*/  pair_udp_send (int*,int) ; 
 int /*<<< orphan*/  pair_udp_send_char (int*,int,int /*<<< orphan*/ ) ; 
 int sock_fanout_open (int,int /*<<< orphan*/ ) ; 
 char* sock_fanout_open_ring (int) ; 
 int sock_fanout_read (int*,char**,int const*) ; 
 int /*<<< orphan*/  sock_fanout_set_cbpf (int) ; 
 int /*<<< orphan*/  sock_fanout_set_ebpf (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_datapath(uint16_t typeflags, int port_off,
			 const int expect1[], const int expect2[])
{
	const int expect0[] = { 0, 0 };
	char *rings[2];
	uint8_t type = typeflags & 0xFF;
	int fds[2], fds_udp[2][2], ret;

	fprintf(stderr, "\ntest: datapath 0x%hx ports %hu,%hu\n",
		typeflags, PORT_BASE, PORT_BASE + port_off);

	fds[0] = sock_fanout_open(typeflags, 0);
	fds[1] = sock_fanout_open(typeflags, 0);
	if (fds[0] == -1 || fds[1] == -1) {
		fprintf(stderr, "ERROR: failed open\n");
		exit(1);
	}
	if (type == PACKET_FANOUT_CBPF)
		sock_fanout_set_cbpf(fds[0]);
	else if (type == PACKET_FANOUT_EBPF)
		sock_fanout_set_ebpf(fds[0]);

	rings[0] = sock_fanout_open_ring(fds[0]);
	rings[1] = sock_fanout_open_ring(fds[1]);
	pair_udp_open(fds_udp[0], PORT_BASE);
	pair_udp_open(fds_udp[1], PORT_BASE + port_off);
	sock_fanout_read(fds, rings, expect0);

	/* Send data, but not enough to overflow a queue */
	pair_udp_send(fds_udp[0], 15);
	pair_udp_send_char(fds_udp[1], 5, DATA_CHAR_1);
	ret = sock_fanout_read(fds, rings, expect1);

	/* Send more data, overflow the queue */
	pair_udp_send_char(fds_udp[0], 15, DATA_CHAR_1);
	/* TODO: ensure consistent order between expect1 and expect2 */
	ret |= sock_fanout_read(fds, rings, expect2);

	if (munmap(rings[1], RING_NUM_FRAMES * getpagesize()) ||
	    munmap(rings[0], RING_NUM_FRAMES * getpagesize())) {
		fprintf(stderr, "close rings\n");
		exit(1);
	}
	if (close(fds_udp[1][1]) || close(fds_udp[1][0]) ||
	    close(fds_udp[0][1]) || close(fds_udp[0][0]) ||
	    close(fds[1]) || close(fds[0])) {
		fprintf(stderr, "close datapath\n");
		exit(1);
	}

	return ret;
}