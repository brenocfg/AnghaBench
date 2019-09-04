#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netns_ipvs {int sync_state; int /*<<< orphan*/  sync_buff_lock; struct ipvs_master_sync_state* ms; } ;
struct ipvs_master_sync_state {struct ip_vs_sync_buff* sync_buff; } ;
struct ip_vs_sync_mesg_v0 {void* size; int /*<<< orphan*/  nr_conns; } ;
struct ip_vs_sync_conn_v0 {void* state; void* flags; int /*<<< orphan*/  daddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  caddr; int /*<<< orphan*/  dport; int /*<<< orphan*/  vport; int /*<<< orphan*/  cport; int /*<<< orphan*/  protocol; scalar_t__ reserved; } ;
struct ip_vs_sync_conn_options {int dummy; } ;
struct ip_vs_sync_buff {scalar_t__ head; scalar_t__ end; scalar_t__ mesg; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct ip_vs_conn {scalar_t__ af; int flags; unsigned int state; int /*<<< orphan*/  in_pkts; struct ip_vs_conn* control; int /*<<< orphan*/  in_seq; TYPE_3__ daddr; TYPE_2__ vaddr; TYPE_1__ caddr; int /*<<< orphan*/  dport; int /*<<< orphan*/  vport; int /*<<< orphan*/  cport; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 unsigned int FULL_CONN_SIZE ; 
 unsigned int IP_VS_CONN_F_HASHED ; 
 int IP_VS_CONN_F_ONE_PACKET ; 
 int IP_VS_CONN_F_SEQ_MASK ; 
 int IP_VS_CONN_F_TEMPLATE ; 
 int IP_VS_STATE_MASTER ; 
 unsigned int SIMPLE_CONN_SIZE ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 void* htons (unsigned int) ; 
 struct ip_vs_sync_buff* ip_vs_sync_buff_create_v0 (struct netns_ipvs*,unsigned int) ; 
 int /*<<< orphan*/  ip_vs_sync_conn (struct netns_ipvs*,struct ip_vs_conn*,int) ; 
 int /*<<< orphan*/  ip_vs_sync_conn_needed (struct netns_ipvs*,struct ip_vs_conn*,int) ; 
 int /*<<< orphan*/  memcpy (struct ip_vs_sync_conn_options*,int /*<<< orphan*/ *,int) ; 
 unsigned int ntohs (void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sb_queue_tail (struct netns_ipvs*,struct ipvs_master_sync_state*) ; 
 int select_master_thread_id (struct netns_ipvs*,struct ip_vs_conn*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int sysctl_sync_threshold (struct netns_ipvs*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ip_vs_sync_conn_v0(struct netns_ipvs *ipvs, struct ip_vs_conn *cp,
			       int pkts)
{
	struct ip_vs_sync_mesg_v0 *m;
	struct ip_vs_sync_conn_v0 *s;
	struct ip_vs_sync_buff *buff;
	struct ipvs_master_sync_state *ms;
	int id;
	unsigned int len;

	if (unlikely(cp->af != AF_INET))
		return;
	/* Do not sync ONE PACKET */
	if (cp->flags & IP_VS_CONN_F_ONE_PACKET)
		return;

	if (!ip_vs_sync_conn_needed(ipvs, cp, pkts))
		return;

	spin_lock_bh(&ipvs->sync_buff_lock);
	if (!(ipvs->sync_state & IP_VS_STATE_MASTER)) {
		spin_unlock_bh(&ipvs->sync_buff_lock);
		return;
	}

	id = select_master_thread_id(ipvs, cp);
	ms = &ipvs->ms[id];
	buff = ms->sync_buff;
	len = (cp->flags & IP_VS_CONN_F_SEQ_MASK) ? FULL_CONN_SIZE :
		SIMPLE_CONN_SIZE;
	if (buff) {
		m = (struct ip_vs_sync_mesg_v0 *) buff->mesg;
		/* Send buffer if it is for v1 */
		if (buff->head + len > buff->end || !m->nr_conns) {
			sb_queue_tail(ipvs, ms);
			ms->sync_buff = NULL;
			buff = NULL;
		}
	}
	if (!buff) {
		buff = ip_vs_sync_buff_create_v0(ipvs, len);
		if (!buff) {
			spin_unlock_bh(&ipvs->sync_buff_lock);
			pr_err("ip_vs_sync_buff_create failed.\n");
			return;
		}
		ms->sync_buff = buff;
	}

	m = (struct ip_vs_sync_mesg_v0 *) buff->mesg;
	s = (struct ip_vs_sync_conn_v0 *) buff->head;

	/* copy members */
	s->reserved = 0;
	s->protocol = cp->protocol;
	s->cport = cp->cport;
	s->vport = cp->vport;
	s->dport = cp->dport;
	s->caddr = cp->caddr.ip;
	s->vaddr = cp->vaddr.ip;
	s->daddr = cp->daddr.ip;
	s->flags = htons(cp->flags & ~IP_VS_CONN_F_HASHED);
	s->state = htons(cp->state);
	if (cp->flags & IP_VS_CONN_F_SEQ_MASK) {
		struct ip_vs_sync_conn_options *opt =
			(struct ip_vs_sync_conn_options *)&s[1];
		memcpy(opt, &cp->in_seq, sizeof(*opt));
	}

	m->nr_conns++;
	m->size = htons(ntohs(m->size) + len);
	buff->head += len;
	spin_unlock_bh(&ipvs->sync_buff_lock);

	/* synchronize its controller if it has */
	cp = cp->control;
	if (cp) {
		if (cp->flags & IP_VS_CONN_F_TEMPLATE)
			pkts = atomic_add_return(1, &cp->in_pkts);
		else
			pkts = sysctl_sync_threshold(ipvs);
		ip_vs_sync_conn(ipvs, cp, pkts);
	}
}