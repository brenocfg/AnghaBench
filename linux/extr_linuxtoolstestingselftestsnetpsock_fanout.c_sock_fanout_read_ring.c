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
struct tpacket2_hdr {int tp_status; } ;

/* Variables and functions */
 int RING_NUM_FRAMES ; 
 int TP_STATUS_USER ; 
 int getpagesize () ; 

__attribute__((used)) static int sock_fanout_read_ring(int fd, void *ring)
{
	struct tpacket2_hdr *header = ring;
	int count = 0;

	while (count < RING_NUM_FRAMES && header->tp_status & TP_STATUS_USER) {
		count++;
		header = ring + (count * getpagesize());
	}

	return count;
}