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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct dccp_ackvec_record {int /*<<< orphan*/  avr_ack_runlen; scalar_t__ avr_ack_ackno; scalar_t__ avr_ack_seqno; int /*<<< orphan*/  avr_node; int /*<<< orphan*/  avr_ack_nonce; scalar_t__ avr_ack_ptr; } ;
struct dccp_ackvec {int /*<<< orphan*/  av_records; scalar_t__ av_overflow; scalar_t__ av_buf_head; scalar_t__ av_buf; scalar_t__ av_buf_ackno; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dccp_ackvec_purge_records (struct dccp_ackvec*) ; 
 int /*<<< orphan*/  dccp_ackvec_record_slab ; 
 int /*<<< orphan*/  dccp_ackvec_runlen (scalar_t__) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 
 struct dccp_ackvec_record* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int dccp_ackvec_update_records(struct dccp_ackvec *av, u64 seqno, u8 nonce_sum)
{
	struct dccp_ackvec_record *avr;

	avr = kmem_cache_alloc(dccp_ackvec_record_slab, GFP_ATOMIC);
	if (avr == NULL)
		return -ENOBUFS;

	avr->avr_ack_seqno  = seqno;
	avr->avr_ack_ptr    = av->av_buf_head;
	avr->avr_ack_ackno  = av->av_buf_ackno;
	avr->avr_ack_nonce  = nonce_sum;
	avr->avr_ack_runlen = dccp_ackvec_runlen(av->av_buf + av->av_buf_head);
	/*
	 * When the buffer overflows, we keep no more than one record. This is
	 * the simplest way of disambiguating sender-Acks dating from before the
	 * overflow from sender-Acks which refer to after the overflow; a simple
	 * solution is preferable here since we are handling an exception.
	 */
	if (av->av_overflow)
		dccp_ackvec_purge_records(av);
	/*
	 * Since GSS is incremented for each packet, the list is automatically
	 * arranged in descending order of @ack_seqno.
	 */
	list_add(&avr->avr_node, &av->av_records);

	dccp_pr_debug("Added Vector, ack_seqno=%llu, ack_ackno=%llu (rl=%u)\n",
		      (unsigned long long)avr->avr_ack_seqno,
		      (unsigned long long)avr->avr_ack_ackno,
		      avr->avr_ack_runlen);
	return 0;
}