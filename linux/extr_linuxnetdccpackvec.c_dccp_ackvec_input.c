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
typedef  int u8 ;
typedef  void* u64 ;
struct sk_buff {int dummy; } ;
struct dccp_ackvec {int* av_buf; int av_buf_head; void* av_buf_ackno; void* av_tail_ackno; } ;
typedef  int s64 ;
typedef  enum dccp_ackvec_states { ____Placeholder_dccp_ackvec_states } dccp_ackvec_states ;
struct TYPE_2__ {void* dccpd_seq; } ;

/* Variables and functions */
 scalar_t__ DCCPAV_MAX_RUNLEN ; 
 int DCCPAV_RECEIVED ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_ackvec_add_new (struct dccp_ackvec*,int,void*,int) ; 
 scalar_t__ dccp_ackvec_is_empty (struct dccp_ackvec*) ; 
 scalar_t__ dccp_ackvec_runlen (int*) ; 
 int dccp_ackvec_state (int*) ; 
 int /*<<< orphan*/  dccp_ackvec_update_old (struct dccp_ackvec*,int,void*,int) ; 
 int dccp_delta_seqno (void*,void*) ; 

void dccp_ackvec_input(struct dccp_ackvec *av, struct sk_buff *skb)
{
	u64 seqno = DCCP_SKB_CB(skb)->dccpd_seq;
	enum dccp_ackvec_states state = DCCPAV_RECEIVED;

	if (dccp_ackvec_is_empty(av)) {
		dccp_ackvec_add_new(av, 1, seqno, state);
		av->av_tail_ackno = seqno;

	} else {
		s64 num_packets = dccp_delta_seqno(av->av_buf_ackno, seqno);
		u8 *current_head = av->av_buf + av->av_buf_head;

		if (num_packets == 1 &&
		    dccp_ackvec_state(current_head) == state &&
		    dccp_ackvec_runlen(current_head) < DCCPAV_MAX_RUNLEN) {

			*current_head   += 1;
			av->av_buf_ackno = seqno;

		} else if (num_packets > 0) {
			dccp_ackvec_add_new(av, num_packets, seqno, state);
		} else {
			dccp_ackvec_update_old(av, num_packets, seqno, state);
		}
	}
}