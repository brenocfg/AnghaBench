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
typedef  int /*<<< orphan*/  val ;
struct tpacket_req {int tp_block_size; int tp_frame_size; int tp_block_nr; int tp_frame_nr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PACKET_RX_RING ; 
 int /*<<< orphan*/  PACKET_VERSION ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int RING_NUM_FRAMES ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int TPACKET_V2 ; 
 int /*<<< orphan*/  exit (int) ; 
 int getpagesize () ; 
 char* mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static char *sock_fanout_open_ring(int fd)
{
	struct tpacket_req req = {
		.tp_block_size = getpagesize(),
		.tp_frame_size = getpagesize(),
		.tp_block_nr   = RING_NUM_FRAMES,
		.tp_frame_nr   = RING_NUM_FRAMES,
	};
	char *ring;
	int val = TPACKET_V2;

	if (setsockopt(fd, SOL_PACKET, PACKET_VERSION, (void *) &val,
		       sizeof(val))) {
		perror("packetsock ring setsockopt version");
		exit(1);
	}
	if (setsockopt(fd, SOL_PACKET, PACKET_RX_RING, (void *) &req,
		       sizeof(req))) {
		perror("packetsock ring setsockopt");
		exit(1);
	}

	ring = mmap(0, req.tp_block_size * req.tp_block_nr,
		    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ring == MAP_FAILED) {
		perror("packetsock ring mmap");
		exit(1);
	}

	return ring;
}