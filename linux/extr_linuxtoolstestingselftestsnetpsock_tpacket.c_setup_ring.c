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
struct ring {int type; int version; int rd_len; int rd_num; int /*<<< orphan*/ * rd; int /*<<< orphan*/  req3; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int PACKET_TX_RING ; 
 int /*<<< orphan*/  SOL_PACKET ; 
#define  TPACKET_V1 130 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 int /*<<< orphan*/  __v1_v2_fill (struct ring*,unsigned int) ; 
 int /*<<< orphan*/  __v1_v2_set_packet_loss_discard (int) ; 
 int /*<<< orphan*/  __v3_fill (struct ring*,unsigned int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ total_bytes ; 
 scalar_t__ total_packets ; 

__attribute__((used)) static void setup_ring(int sock, struct ring *ring, int version, int type)
{
	int ret = 0;
	unsigned int blocks = 256;

	ring->type = type;
	ring->version = version;

	switch (version) {
	case TPACKET_V1:
	case TPACKET_V2:
		if (type == PACKET_TX_RING)
			__v1_v2_set_packet_loss_discard(sock);
		__v1_v2_fill(ring, blocks);
		ret = setsockopt(sock, SOL_PACKET, type, &ring->req,
				 sizeof(ring->req));
		break;

	case TPACKET_V3:
		__v3_fill(ring, blocks, type);
		ret = setsockopt(sock, SOL_PACKET, type, &ring->req3,
				 sizeof(ring->req3));
		break;
	}

	if (ret == -1) {
		perror("setsockopt");
		exit(1);
	}

	ring->rd_len = ring->rd_num * sizeof(*ring->rd);
	ring->rd = malloc(ring->rd_len);
	if (ring->rd == NULL) {
		perror("malloc");
		exit(1);
	}

	total_packets = 0;
	total_bytes = 0;
}