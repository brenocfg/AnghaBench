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
struct packet_fanout {int type; int /*<<< orphan*/  bpf_prog; int /*<<< orphan*/  rr_cur; } ;

/* Variables and functions */
#define  PACKET_FANOUT_CBPF 130 
#define  PACKET_FANOUT_EBPF 129 
#define  PACKET_FANOUT_LB 128 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fanout_init_data(struct packet_fanout *f)
{
	switch (f->type) {
	case PACKET_FANOUT_LB:
		atomic_set(&f->rr_cur, 0);
		break;
	case PACKET_FANOUT_CBPF:
	case PACKET_FANOUT_EBPF:
		RCU_INIT_POINTER(f->bpf_prog, NULL);
		break;
	}
}