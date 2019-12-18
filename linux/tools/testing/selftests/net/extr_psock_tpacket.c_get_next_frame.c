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
typedef  void uint8_t ;
struct TYPE_4__ {int tp_frame_size; } ;
struct ring {int version; TYPE_2__ req3; TYPE_1__* rd; } ;
struct TYPE_3__ {void* iov_base; } ;

/* Variables and functions */
#define  TPACKET_V1 130 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 int /*<<< orphan*/  bug_on (int) ; 

__attribute__((used)) static inline void *get_next_frame(struct ring *ring, int n)
{
	uint8_t *f0 = ring->rd[0].iov_base;

	switch (ring->version) {
	case TPACKET_V1:
	case TPACKET_V2:
		return ring->rd[n].iov_base;
	case TPACKET_V3:
		return f0 + (n * ring->req3.tp_frame_size);
	default:
		bug_on(1);
	}
}