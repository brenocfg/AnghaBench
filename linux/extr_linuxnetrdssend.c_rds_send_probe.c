#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_10__ {int /*<<< orphan*/  h_flags; } ;
struct TYPE_9__ {TYPE_4__ i_hdr; struct rds_conn_path* i_conn_path; TYPE_6__* i_conn; } ;
struct TYPE_7__ {int op_active; } ;
struct rds_message {TYPE_3__ m_inc; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_conn_item; TYPE_1__ data; int /*<<< orphan*/  m_daddr; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_send_w; TYPE_6__* cp_conn; int /*<<< orphan*/  cp_lock; int /*<<< orphan*/  cp_next_tx_seq; int /*<<< orphan*/  cp_send_queue; } ;
typedef  int /*<<< orphan*/  npaths ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_11__ {int /*<<< orphan*/  c_my_gen_num; TYPE_2__* c_trans; int /*<<< orphan*/  c_fcong; int /*<<< orphan*/  c_faddr; } ;
struct TYPE_8__ {scalar_t__ t_mp_capable; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RDS_EXTHDR_GEN_NUM ; 
 int /*<<< orphan*/  RDS_EXTHDR_NPATHS ; 
 scalar_t__ RDS_HS_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDS_MPATH_WORKERS ; 
 int /*<<< orphan*/  RDS_MSG_ON_CONN ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int rds_cong_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_conn_path_connect_if_down (struct rds_conn_path*) ; 
 int /*<<< orphan*/  rds_destroy_pending (TYPE_6__*) ; 
 int /*<<< orphan*/  rds_message_add_extension (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rds_message_addref (struct rds_message*) ; 
 struct rds_message* rds_message_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_message_populate_header (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_message_put (struct rds_message*) ; 
 int /*<<< orphan*/  rds_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  s_send_pong ; 
 int /*<<< orphan*/  s_send_queued ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
rds_send_probe(struct rds_conn_path *cp, __be16 sport,
	       __be16 dport, u8 h_flags)
{
	struct rds_message *rm;
	unsigned long flags;
	int ret = 0;

	rm = rds_message_alloc(0, GFP_ATOMIC);
	if (!rm) {
		ret = -ENOMEM;
		goto out;
	}

	rm->m_daddr = cp->cp_conn->c_faddr;
	rm->data.op_active = 1;

	rds_conn_path_connect_if_down(cp);

	ret = rds_cong_wait(cp->cp_conn->c_fcong, dport, 1, NULL);
	if (ret)
		goto out;

	spin_lock_irqsave(&cp->cp_lock, flags);
	list_add_tail(&rm->m_conn_item, &cp->cp_send_queue);
	set_bit(RDS_MSG_ON_CONN, &rm->m_flags);
	rds_message_addref(rm);
	rm->m_inc.i_conn = cp->cp_conn;
	rm->m_inc.i_conn_path = cp;

	rds_message_populate_header(&rm->m_inc.i_hdr, sport, dport,
				    cp->cp_next_tx_seq);
	rm->m_inc.i_hdr.h_flags |= h_flags;
	cp->cp_next_tx_seq++;

	if (RDS_HS_PROBE(be16_to_cpu(sport), be16_to_cpu(dport)) &&
	    cp->cp_conn->c_trans->t_mp_capable) {
		u16 npaths = cpu_to_be16(RDS_MPATH_WORKERS);
		u32 my_gen_num = cpu_to_be32(cp->cp_conn->c_my_gen_num);

		rds_message_add_extension(&rm->m_inc.i_hdr,
					  RDS_EXTHDR_NPATHS, &npaths,
					  sizeof(npaths));
		rds_message_add_extension(&rm->m_inc.i_hdr,
					  RDS_EXTHDR_GEN_NUM,
					  &my_gen_num,
					  sizeof(u32));
	}
	spin_unlock_irqrestore(&cp->cp_lock, flags);

	rds_stats_inc(s_send_queued);
	rds_stats_inc(s_send_pong);

	/* schedule the send work on rds_wq */
	rcu_read_lock();
	if (!rds_destroy_pending(cp->cp_conn))
		queue_delayed_work(rds_wq, &cp->cp_send_w, 1);
	rcu_read_unlock();

	rds_message_put(rm);
	return 0;

out:
	if (rm)
		rds_message_put(rm);
	return ret;
}