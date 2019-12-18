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
struct tpacket_req3 {int /*<<< orphan*/  tp_feature_req_word; scalar_t__ tp_sizeof_priv; int /*<<< orphan*/  tp_retire_blk_tov; } ;
struct tpacket_req {int tp_block_nr; scalar_t__ tp_block_size; unsigned int tp_frame_size; int tp_frame_nr; } ;
union tpacket_req_u {struct tpacket_req3 req3; struct tpacket_req req; } ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {struct sk_buff_head sk_receive_queue; struct sk_buff_head sk_write_queue; } ;
struct pgv {int dummy; } ;
struct packet_ring_buffer {int pg_vec; int frames_per_block; int frame_max; int frame_size; int pg_vec_pages; int /*<<< orphan*/  pg_vec_len; int /*<<< orphan*/  pg_vec_order; scalar_t__ head; } ;
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct packet_sock {int tp_version; unsigned int tp_hdrlen; unsigned int tp_reserve; int running; int /*<<< orphan*/  bind_lock; scalar_t__ num; int /*<<< orphan*/  pg_vec_lock; int /*<<< orphan*/  mapped; struct packet_ring_buffer rx_ring; TYPE_1__ prot_hook; struct packet_ring_buffer tx_ring; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ BLK_PLUS_PRIV (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_ALIGNED (scalar_t__) ; 
 int PAGE_SIZE ; 
 unsigned int TPACKET2_HDRLEN ; 
 unsigned int TPACKET3_HDRLEN ; 
 int TPACKET_ALIGNMENT ; 
 unsigned int TPACKET_HDRLEN ; 
#define  TPACKET_V1 130 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 int UINT_MAX ; 
 int /*<<< orphan*/  __unregister_prot_hook (struct sock*,int) ; 
 struct pgv* alloc_pg_vec (struct tpacket_req*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pg_vec (struct pgv*,int,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  init_prb_bdqc (struct packet_sock*,struct packet_ring_buffer*,struct pgv*,union tpacket_req_u*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_rcv ; 
 scalar_t__ packet_read_pending (struct packet_ring_buffer*) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  prb_shutdown_retire_blk_timer (struct packet_sock*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  register_prot_hook (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int,int) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  tpacket_rcv ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int packet_set_ring(struct sock *sk, union tpacket_req_u *req_u,
		int closing, int tx_ring)
{
	struct pgv *pg_vec = NULL;
	struct packet_sock *po = pkt_sk(sk);
	int was_running, order = 0;
	struct packet_ring_buffer *rb;
	struct sk_buff_head *rb_queue;
	__be16 num;
	int err = -EINVAL;
	/* Added to avoid minimal code churn */
	struct tpacket_req *req = &req_u->req;

	rb = tx_ring ? &po->tx_ring : &po->rx_ring;
	rb_queue = tx_ring ? &sk->sk_write_queue : &sk->sk_receive_queue;

	err = -EBUSY;
	if (!closing) {
		if (atomic_read(&po->mapped))
			goto out;
		if (packet_read_pending(rb))
			goto out;
	}

	if (req->tp_block_nr) {
		unsigned int min_frame_size;

		/* Sanity tests and some calculations */
		err = -EBUSY;
		if (unlikely(rb->pg_vec))
			goto out;

		switch (po->tp_version) {
		case TPACKET_V1:
			po->tp_hdrlen = TPACKET_HDRLEN;
			break;
		case TPACKET_V2:
			po->tp_hdrlen = TPACKET2_HDRLEN;
			break;
		case TPACKET_V3:
			po->tp_hdrlen = TPACKET3_HDRLEN;
			break;
		}

		err = -EINVAL;
		if (unlikely((int)req->tp_block_size <= 0))
			goto out;
		if (unlikely(!PAGE_ALIGNED(req->tp_block_size)))
			goto out;
		min_frame_size = po->tp_hdrlen + po->tp_reserve;
		if (po->tp_version >= TPACKET_V3 &&
		    req->tp_block_size <
		    BLK_PLUS_PRIV((u64)req_u->req3.tp_sizeof_priv) + min_frame_size)
			goto out;
		if (unlikely(req->tp_frame_size < min_frame_size))
			goto out;
		if (unlikely(req->tp_frame_size & (TPACKET_ALIGNMENT - 1)))
			goto out;

		rb->frames_per_block = req->tp_block_size / req->tp_frame_size;
		if (unlikely(rb->frames_per_block == 0))
			goto out;
		if (unlikely(rb->frames_per_block > UINT_MAX / req->tp_block_nr))
			goto out;
		if (unlikely((rb->frames_per_block * req->tp_block_nr) !=
					req->tp_frame_nr))
			goto out;

		err = -ENOMEM;
		order = get_order(req->tp_block_size);
		pg_vec = alloc_pg_vec(req, order);
		if (unlikely(!pg_vec))
			goto out;
		switch (po->tp_version) {
		case TPACKET_V3:
			/* Block transmit is not supported yet */
			if (!tx_ring) {
				init_prb_bdqc(po, rb, pg_vec, req_u);
			} else {
				struct tpacket_req3 *req3 = &req_u->req3;

				if (req3->tp_retire_blk_tov ||
				    req3->tp_sizeof_priv ||
				    req3->tp_feature_req_word) {
					err = -EINVAL;
					goto out_free_pg_vec;
				}
			}
			break;
		default:
			break;
		}
	}
	/* Done */
	else {
		err = -EINVAL;
		if (unlikely(req->tp_frame_nr))
			goto out;
	}


	/* Detach socket from network */
	spin_lock(&po->bind_lock);
	was_running = po->running;
	num = po->num;
	if (was_running) {
		po->num = 0;
		__unregister_prot_hook(sk, false);
	}
	spin_unlock(&po->bind_lock);

	synchronize_net();

	err = -EBUSY;
	mutex_lock(&po->pg_vec_lock);
	if (closing || atomic_read(&po->mapped) == 0) {
		err = 0;
		spin_lock_bh(&rb_queue->lock);
		swap(rb->pg_vec, pg_vec);
		rb->frame_max = (req->tp_frame_nr - 1);
		rb->head = 0;
		rb->frame_size = req->tp_frame_size;
		spin_unlock_bh(&rb_queue->lock);

		swap(rb->pg_vec_order, order);
		swap(rb->pg_vec_len, req->tp_block_nr);

		rb->pg_vec_pages = req->tp_block_size/PAGE_SIZE;
		po->prot_hook.func = (po->rx_ring.pg_vec) ?
						tpacket_rcv : packet_rcv;
		skb_queue_purge(rb_queue);
		if (atomic_read(&po->mapped))
			pr_err("packet_mmap: vma is busy: %d\n",
			       atomic_read(&po->mapped));
	}
	mutex_unlock(&po->pg_vec_lock);

	spin_lock(&po->bind_lock);
	if (was_running) {
		po->num = num;
		register_prot_hook(sk);
	}
	spin_unlock(&po->bind_lock);
	if (pg_vec && (po->tp_version > TPACKET_V2)) {
		/* Because we don't support block-based V3 on tx-ring */
		if (!tx_ring)
			prb_shutdown_retire_blk_timer(po, rb_queue);
	}

out_free_pg_vec:
	if (pg_vec)
		free_pg_vec(pg_vec, order, req->tp_block_nr);
out:
	return err;
}