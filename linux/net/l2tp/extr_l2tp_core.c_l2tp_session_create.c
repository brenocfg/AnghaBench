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
typedef  void* u32 ;
struct l2tp_tunnel {int tunnel_id; int /*<<< orphan*/  version; int /*<<< orphan*/  debug; } ;
struct l2tp_session_cfg {int /*<<< orphan*/  peer_cookie_len; int /*<<< orphan*/ * peer_cookie; int /*<<< orphan*/  cookie_len; int /*<<< orphan*/ * cookie; int /*<<< orphan*/  l2specific_type; int /*<<< orphan*/  reorder_timeout; int /*<<< orphan*/  lns_mode; int /*<<< orphan*/  recv_seq; int /*<<< orphan*/  send_seq; int /*<<< orphan*/  debug; int /*<<< orphan*/  pw_type; } ;
struct l2tp_session {int session_id; int nr_max; int nr_window_size; int nr_oos_count_max; int reorder_skip; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  build_header; int /*<<< orphan*/ * peer_cookie; int /*<<< orphan*/  peer_cookie_len; int /*<<< orphan*/ * cookie; int /*<<< orphan*/  cookie_len; int /*<<< orphan*/  l2specific_type; int /*<<< orphan*/  reorder_timeout; int /*<<< orphan*/  lns_mode; int /*<<< orphan*/  recv_seq; int /*<<< orphan*/  send_seq; int /*<<< orphan*/  debug; int /*<<< orphan*/  pwtype; int /*<<< orphan*/  global_hlist; int /*<<< orphan*/  hlist; int /*<<< orphan*/  reorder_q; int /*<<< orphan*/ * name; scalar_t__ nr; void* peer_session_id; struct l2tp_tunnel* tunnel; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct l2tp_session* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L2TP_HDR_VER_2 ; 
 int /*<<< orphan*/  L2TP_SESSION_MAGIC ; 
 struct l2tp_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_build_l2tpv2_header ; 
 int /*<<< orphan*/  l2tp_build_l2tpv3_header ; 
 int /*<<< orphan*/  l2tp_session_set_header_len (struct l2tp_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,int) ; 

struct l2tp_session *l2tp_session_create(int priv_size, struct l2tp_tunnel *tunnel, u32 session_id, u32 peer_session_id, struct l2tp_session_cfg *cfg)
{
	struct l2tp_session *session;

	session = kzalloc(sizeof(struct l2tp_session) + priv_size, GFP_KERNEL);
	if (session != NULL) {
		session->magic = L2TP_SESSION_MAGIC;
		session->tunnel = tunnel;

		session->session_id = session_id;
		session->peer_session_id = peer_session_id;
		session->nr = 0;
		if (tunnel->version == L2TP_HDR_VER_2)
			session->nr_max = 0xffff;
		else
			session->nr_max = 0xffffff;
		session->nr_window_size = session->nr_max / 2;
		session->nr_oos_count_max = 4;

		/* Use NR of first received packet */
		session->reorder_skip = 1;

		sprintf(&session->name[0], "sess %u/%u",
			tunnel->tunnel_id, session->session_id);

		skb_queue_head_init(&session->reorder_q);

		INIT_HLIST_NODE(&session->hlist);
		INIT_HLIST_NODE(&session->global_hlist);

		/* Inherit debug options from tunnel */
		session->debug = tunnel->debug;

		if (cfg) {
			session->pwtype = cfg->pw_type;
			session->debug = cfg->debug;
			session->send_seq = cfg->send_seq;
			session->recv_seq = cfg->recv_seq;
			session->lns_mode = cfg->lns_mode;
			session->reorder_timeout = cfg->reorder_timeout;
			session->l2specific_type = cfg->l2specific_type;
			session->cookie_len = cfg->cookie_len;
			memcpy(&session->cookie[0], &cfg->cookie[0], cfg->cookie_len);
			session->peer_cookie_len = cfg->peer_cookie_len;
			memcpy(&session->peer_cookie[0], &cfg->peer_cookie[0], cfg->peer_cookie_len);
		}

		if (tunnel->version == L2TP_HDR_VER_2)
			session->build_header = l2tp_build_l2tpv2_header;
		else
			session->build_header = l2tp_build_l2tpv3_header;

		l2tp_session_set_header_len(session, tunnel->version);

		refcount_set(&session->ref_count, 1);

		return session;
	}

	return ERR_PTR(-ENOMEM);
}