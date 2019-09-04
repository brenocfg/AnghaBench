#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct txq_entry_t {size_t tcp_pending_ack_idx; } ;
struct TYPE_2__ {size_t ack_num; size_t session_index; struct txq_entry_t* txqe; } ;

/* Variables and functions */
 size_t MAX_PENDING_ACKS ; 
 size_t pending_acks ; 
 TYPE_1__* pending_acks_info ; 
 size_t pending_base ; 

__attribute__((used)) static inline int add_tcp_pending_ack(u32 ack, u32 session_index,
				      struct txq_entry_t *txqe)
{
	u32 i = pending_base + pending_acks;

	if (i < MAX_PENDING_ACKS) {
		pending_acks_info[i].ack_num = ack;
		pending_acks_info[i].txqe = txqe;
		pending_acks_info[i].session_index = session_index;
		txqe->tcp_pending_ack_idx = i;
		pending_acks++;
	}
	return 0;
}