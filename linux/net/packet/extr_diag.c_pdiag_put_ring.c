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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ feature_req_word; scalar_t__ blk_sizeof_priv; scalar_t__ retire_blk_tov; } ;
struct packet_ring_buffer {int pg_vec_pages; TYPE_1__ prb_bdqc; scalar_t__ frame_max; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  pg_vec_len; int /*<<< orphan*/  pg_vec; } ;
struct packet_diag_ring {int pdr_block_size; scalar_t__ pdr_features; scalar_t__ pdr_sizeof_priv; scalar_t__ pdr_retire_tmo; scalar_t__ pdr_frame_nr; int /*<<< orphan*/  pdr_frame_size; int /*<<< orphan*/  pdr_block_nr; } ;
typedef  int /*<<< orphan*/  pdr ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int TPACKET_V2 ; 
 int nla_put (struct sk_buff*,int,int,struct packet_diag_ring*) ; 

__attribute__((used)) static int pdiag_put_ring(struct packet_ring_buffer *ring, int ver, int nl_type,
		struct sk_buff *nlskb)
{
	struct packet_diag_ring pdr;

	if (!ring->pg_vec)
		return 0;

	pdr.pdr_block_size = ring->pg_vec_pages << PAGE_SHIFT;
	pdr.pdr_block_nr = ring->pg_vec_len;
	pdr.pdr_frame_size = ring->frame_size;
	pdr.pdr_frame_nr = ring->frame_max + 1;

	if (ver > TPACKET_V2) {
		pdr.pdr_retire_tmo = ring->prb_bdqc.retire_blk_tov;
		pdr.pdr_sizeof_priv = ring->prb_bdqc.blk_sizeof_priv;
		pdr.pdr_features = ring->prb_bdqc.feature_req_word;
	} else {
		pdr.pdr_retire_tmo = 0;
		pdr.pdr_sizeof_priv = 0;
		pdr.pdr_features = 0;
	}

	return nla_put(nlskb, nl_type, sizeof(pdr), &pdr);
}