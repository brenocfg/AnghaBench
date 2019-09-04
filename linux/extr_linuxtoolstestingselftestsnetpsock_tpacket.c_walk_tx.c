#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union frame_map {TYPE_5__* v2; void* raw; TYPE_3__* v1; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct tpacket3_hdr {size_t tp_snaplen; size_t tp_len; int /*<<< orphan*/  tp_next_offset; } ;
struct sockaddr_ll {int /*<<< orphan*/  sll_ifindex; int /*<<< orphan*/  sll_halen; int /*<<< orphan*/  sll_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int tp_frame_nr; } ;
struct ring {int version; int rd_num; scalar_t__ type; TYPE_1__ req3; } ;
struct pollfd {int fd; int events; scalar_t__ revents; } ;
typedef  int /*<<< orphan*/  pfd ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_9__ {size_t tp_snaplen; size_t tp_len; } ;
struct TYPE_10__ {TYPE_4__ tp_h; } ;
struct TYPE_7__ {size_t tp_snaplen; size_t tp_len; } ;
struct TYPE_8__ {TYPE_2__ tp_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int NUM_PACKETS ; 
 scalar_t__ PACKET_TX_RING ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int POLLERR ; 
 int POLLOUT ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  TPACKET2_HDRLEN ; 
 int /*<<< orphan*/  TPACKET3_HDRLEN ; 
 int /*<<< orphan*/  TPACKET_HDRLEN ; 
#define  TPACKET_V1 130 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 scalar_t__ __tx_kernel_ready (void*,int) ; 
 int /*<<< orphan*/  __tx_user_ready (void*,int) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bug_on (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  create_payload (char*,size_t*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned int,...) ; 
 void* get_next_frame (struct ring*,unsigned int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_nametoindex (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  memset (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pair_udp_setfilter (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sendto (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_bar_update () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_payload (char*,int) ; 
 size_t total_bytes ; 
 int total_packets ; 

__attribute__((used)) static void walk_tx(int sock, struct ring *ring)
{
	struct pollfd pfd;
	int rcv_sock, ret;
	size_t packet_len;
	union frame_map ppd;
	char packet[1024];
	unsigned int frame_num = 0, got = 0;
	struct sockaddr_ll ll = {
		.sll_family = PF_PACKET,
		.sll_halen = ETH_ALEN,
	};
	int nframes;

	/* TPACKET_V{1,2} sets up the ring->rd* related variables based
	 * on frames (e.g., rd_num is tp_frame_nr) whereas V3 sets these
	 * up based on blocks (e.g, rd_num is  tp_block_nr)
	 */
	if (ring->version <= TPACKET_V2)
		nframes = ring->rd_num;
	else
		nframes = ring->req3.tp_frame_nr;

	bug_on(ring->type != PACKET_TX_RING);
	bug_on(nframes < NUM_PACKETS);

	rcv_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (rcv_sock == -1) {
		perror("socket");
		exit(1);
	}

	pair_udp_setfilter(rcv_sock);

	ll.sll_ifindex = if_nametoindex("lo");
	ret = bind(rcv_sock, (struct sockaddr *) &ll, sizeof(ll));
	if (ret == -1) {
		perror("bind");
		exit(1);
	}

	memset(&pfd, 0, sizeof(pfd));
	pfd.fd = sock;
	pfd.events = POLLOUT | POLLERR;
	pfd.revents = 0;

	total_packets = NUM_PACKETS;
	create_payload(packet, &packet_len);

	while (total_packets > 0) {
		void *next = get_next_frame(ring, frame_num);

		while (__tx_kernel_ready(next, ring->version) &&
		       total_packets > 0) {
			ppd.raw = next;

			switch (ring->version) {
			case TPACKET_V1:
				ppd.v1->tp_h.tp_snaplen = packet_len;
				ppd.v1->tp_h.tp_len = packet_len;

				memcpy((uint8_t *) ppd.raw + TPACKET_HDRLEN -
				       sizeof(struct sockaddr_ll), packet,
				       packet_len);
				total_bytes += ppd.v1->tp_h.tp_snaplen;
				break;

			case TPACKET_V2:
				ppd.v2->tp_h.tp_snaplen = packet_len;
				ppd.v2->tp_h.tp_len = packet_len;

				memcpy((uint8_t *) ppd.raw + TPACKET2_HDRLEN -
				       sizeof(struct sockaddr_ll), packet,
				       packet_len);
				total_bytes += ppd.v2->tp_h.tp_snaplen;
				break;
			case TPACKET_V3: {
				struct tpacket3_hdr *tx = next;

				tx->tp_snaplen = packet_len;
				tx->tp_len = packet_len;
				tx->tp_next_offset = 0;

				memcpy((uint8_t *)tx + TPACKET3_HDRLEN -
				       sizeof(struct sockaddr_ll), packet,
				       packet_len);
				total_bytes += tx->tp_snaplen;
				break;
			}
			}

			status_bar_update();
			total_packets--;

			__tx_user_ready(next, ring->version);

			frame_num = (frame_num + 1) % nframes;
		}

		poll(&pfd, 1, 1);
	}

	bug_on(total_packets != 0);

	ret = sendto(sock, NULL, 0, 0, NULL, 0);
	if (ret == -1) {
		perror("sendto");
		exit(1);
	}

	while ((ret = recvfrom(rcv_sock, packet, sizeof(packet),
			       0, NULL, NULL)) > 0 &&
	       total_packets < NUM_PACKETS) {
		got += ret;
		test_payload(packet, ret);

		status_bar_update();
		total_packets++;
	}

	close(rcv_sock);

	if (total_packets != NUM_PACKETS) {
		fprintf(stderr, "walk_v%d_rx: received %u out of %u pkts\n",
			ring->version, total_packets, NUM_PACKETS);
		exit(1);
	}

	fprintf(stderr, " %u pkts (%u bytes)", NUM_PACKETS, got);
}