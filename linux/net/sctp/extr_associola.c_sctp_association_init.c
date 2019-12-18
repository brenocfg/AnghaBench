#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct sock {int sk_rcvbuf; scalar_t__ sk_family; } ;
struct TYPE_13__ {int /*<<< orphan*/  sinit_max_init_timeo; int /*<<< orphan*/  sinit_max_attempts; int /*<<< orphan*/  sinit_num_ostreams; int /*<<< orphan*/  sinit_max_instreams; } ;
struct TYPE_12__ {int /*<<< orphan*/  srto_min; int /*<<< orphan*/  srto_max; int /*<<< orphan*/  srto_initial; } ;
struct TYPE_20__ {int /*<<< orphan*/  sasoc_asocmaxrxt; int /*<<< orphan*/  sasoc_cookie_life; } ;
struct sctp_sock {int autoclose; int /*<<< orphan*/  default_rcv_context; int /*<<< orphan*/  default_timetolive; int /*<<< orphan*/  default_context; int /*<<< orphan*/  default_flags; int /*<<< orphan*/  default_ppid; int /*<<< orphan*/  default_stream; int /*<<< orphan*/  pathmtu; TYPE_2__ initmsg; int /*<<< orphan*/  subscribe; int /*<<< orphan*/  max_burst; int /*<<< orphan*/  param_flags; int /*<<< orphan*/  sackfreq; int /*<<< orphan*/  sackdelay; int /*<<< orphan*/  dscp; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  pathmaxrxt; int /*<<< orphan*/  hbinterval; TYPE_1__ rtoinfo; int /*<<< orphan*/  pf_retrans; TYPE_9__ assocparams; int /*<<< orphan*/  user_frag; } ;
struct sctp_paramhdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {int /*<<< orphan*/  port; } ;
struct TYPE_19__ {TYPE_7__ bind_addr; } ;
struct sctp_endpoint {TYPE_10__* auth_chunk_list; TYPE_10__* auth_hmacs_list; int /*<<< orphan*/  strreset_enable; int /*<<< orphan*/  active_key_id; TYPE_8__ base; } ;
struct TYPE_17__ {struct sock* sk; int /*<<< orphan*/  inqueue; int /*<<< orphan*/  bind_addr; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {scalar_t__ auth_random; int /*<<< orphan*/  auth_chunks; int /*<<< orphan*/  auth_hmacs; int /*<<< orphan*/  sinit_num_ostreams; scalar_t__ initial_tsn; int /*<<< orphan*/  my_port; int /*<<< orphan*/  my_vtag; int /*<<< orphan*/  sinit_max_instreams; } ;
struct TYPE_14__ {int sack_needed; int sack_generation; int ipv4_address; int ipv6_address; int /*<<< orphan*/  transport_addr_list; int /*<<< orphan*/  rwnd; } ;
struct sctp_association {int rto_initial; int rto_max; int sackdelay; int* timeouts; int rwnd; int a_rwnd; struct sctp_endpoint* ep; TYPE_6__ base; int /*<<< orphan*/  stream; TYPE_5__ c; int /*<<< orphan*/  strreset_enable; int /*<<< orphan*/  active_key_id; int /*<<< orphan*/  endpoint_shared_keys; int /*<<< orphan*/  default_rcv_context; int /*<<< orphan*/  default_timetolive; int /*<<< orphan*/  default_context; int /*<<< orphan*/  default_flags; int /*<<< orphan*/  default_ppid; int /*<<< orphan*/  default_stream; int /*<<< orphan*/  asocs; TYPE_3__ peer; int /*<<< orphan*/  pathmtu; int /*<<< orphan*/  ulpq; int /*<<< orphan*/  outqueue; int /*<<< orphan*/  asconf_ack_list; int /*<<< orphan*/  addip_chunk_list; scalar_t__ strreset_outseq; scalar_t__ addip_serial; scalar_t__ ctsn_ack_point; scalar_t__ last_cwr_tsn; scalar_t__ highest_sacked; scalar_t__ adv_peer_ack_point; scalar_t__ next_tsn; int /*<<< orphan*/  wait; int /*<<< orphan*/  rmem_alloc; void* max_init_timeo; int /*<<< orphan*/  max_init_attempts; int /*<<< orphan*/ * timers; int /*<<< orphan*/  subscribe; int /*<<< orphan*/  max_burst; int /*<<< orphan*/  param_flags; int /*<<< orphan*/  sackfreq; int /*<<< orphan*/  dscp; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  pathmaxrxt; void* hbinterval; void* rto_min; int /*<<< orphan*/  pf_retrans; int /*<<< orphan*/  max_retrans; int /*<<< orphan*/  user_frag; int /*<<< orphan*/  cookie_life; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum sctp_scope { ____Placeholder_sctp_scope } sctp_scope ;
struct TYPE_15__ {int /*<<< orphan*/  length; } ;
struct TYPE_11__ {TYPE_4__ param_hdr; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SCTP_AUTH_RANDOM_LENGTH ; 
 int /*<<< orphan*/  SCTP_DEFAULT_MAXWINDOW ; 
 int SCTP_DEFAULT_MINWINDOW ; 
 int /*<<< orphan*/  SCTP_EP_TYPE_ASSOCIATION ; 
 size_t SCTP_EVENT_TIMEOUT_AUTOCLOSE ; 
 int SCTP_EVENT_TIMEOUT_NONE ; 
 size_t SCTP_EVENT_TIMEOUT_SACK ; 
 size_t SCTP_EVENT_TIMEOUT_T1_COOKIE ; 
 size_t SCTP_EVENT_TIMEOUT_T1_INIT ; 
 size_t SCTP_EVENT_TIMEOUT_T2_SHUTDOWN ; 
 size_t SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD ; 
 int SCTP_NUM_TIMEOUT_TYPES ; 
 int /*<<< orphan*/  SCTP_PARAM_RANDOM ; 
 int /*<<< orphan*/  SCTP_STATE_CLOSED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (struct sctp_paramhdr*,scalar_t__) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_to_ktime (int /*<<< orphan*/ ) ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_assoc_bh_rcv ; 
 int /*<<< orphan*/  sctp_assoc_update_frag_point (struct sctp_association*) ; 
 scalar_t__ sctp_auth_asoc_copy_shkeys (struct sctp_endpoint const*,struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bind_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_endpoint_hold (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  sctp_endpoint_put (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  sctp_generate_tag (struct sctp_endpoint const*) ; 
 scalar_t__ sctp_generate_tsn (struct sctp_endpoint const*) ; 
 int /*<<< orphan*/  sctp_inq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inq_set_th_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_outq_init (struct sctp_association*,int /*<<< orphan*/ *) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_stream_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sctp_timer_events ; 
 int /*<<< orphan*/  sctp_ulpq_init (int /*<<< orphan*/ *,struct sctp_association*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_association *sctp_association_init(
					struct sctp_association *asoc,
					const struct sctp_endpoint *ep,
					const struct sock *sk,
					enum sctp_scope scope, gfp_t gfp)
{
	struct sctp_sock *sp;
	struct sctp_paramhdr *p;
	int i;

	/* Retrieve the SCTP per socket area.  */
	sp = sctp_sk((struct sock *)sk);

	/* Discarding const is appropriate here.  */
	asoc->ep = (struct sctp_endpoint *)ep;
	asoc->base.sk = (struct sock *)sk;

	sctp_endpoint_hold(asoc->ep);
	sock_hold(asoc->base.sk);

	/* Initialize the common base substructure.  */
	asoc->base.type = SCTP_EP_TYPE_ASSOCIATION;

	/* Initialize the object handling fields.  */
	refcount_set(&asoc->base.refcnt, 1);

	/* Initialize the bind addr area.  */
	sctp_bind_addr_init(&asoc->base.bind_addr, ep->base.bind_addr.port);

	asoc->state = SCTP_STATE_CLOSED;
	asoc->cookie_life = ms_to_ktime(sp->assocparams.sasoc_cookie_life);
	asoc->user_frag = sp->user_frag;

	/* Set the association max_retrans and RTO values from the
	 * socket values.
	 */
	asoc->max_retrans = sp->assocparams.sasoc_asocmaxrxt;
	asoc->pf_retrans  = sp->pf_retrans;

	asoc->rto_initial = msecs_to_jiffies(sp->rtoinfo.srto_initial);
	asoc->rto_max = msecs_to_jiffies(sp->rtoinfo.srto_max);
	asoc->rto_min = msecs_to_jiffies(sp->rtoinfo.srto_min);

	/* Initialize the association's heartbeat interval based on the
	 * sock configured value.
	 */
	asoc->hbinterval = msecs_to_jiffies(sp->hbinterval);

	/* Initialize path max retrans value. */
	asoc->pathmaxrxt = sp->pathmaxrxt;

	asoc->flowlabel = sp->flowlabel;
	asoc->dscp = sp->dscp;

	/* Set association default SACK delay */
	asoc->sackdelay = msecs_to_jiffies(sp->sackdelay);
	asoc->sackfreq = sp->sackfreq;

	/* Set the association default flags controlling
	 * Heartbeat, SACK delay, and Path MTU Discovery.
	 */
	asoc->param_flags = sp->param_flags;

	/* Initialize the maximum number of new data packets that can be sent
	 * in a burst.
	 */
	asoc->max_burst = sp->max_burst;

	asoc->subscribe = sp->subscribe;

	/* initialize association timers */
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T1_COOKIE] = asoc->rto_initial;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T1_INIT] = asoc->rto_initial;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = asoc->rto_initial;

	/* sctpimpguide Section 2.12.2
	 * If the 'T5-shutdown-guard' timer is used, it SHOULD be set to the
	 * recommended value of 5 times 'RTO.Max'.
	 */
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD]
		= 5 * asoc->rto_max;

	asoc->timeouts[SCTP_EVENT_TIMEOUT_SACK] = asoc->sackdelay;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE] = sp->autoclose * HZ;

	/* Initializes the timers */
	for (i = SCTP_EVENT_TIMEOUT_NONE; i < SCTP_NUM_TIMEOUT_TYPES; ++i)
		timer_setup(&asoc->timers[i], sctp_timer_events[i], 0);

	/* Pull default initialization values from the sock options.
	 * Note: This assumes that the values have already been
	 * validated in the sock.
	 */
	asoc->c.sinit_max_instreams = sp->initmsg.sinit_max_instreams;
	asoc->c.sinit_num_ostreams  = sp->initmsg.sinit_num_ostreams;
	asoc->max_init_attempts	= sp->initmsg.sinit_max_attempts;

	asoc->max_init_timeo =
		 msecs_to_jiffies(sp->initmsg.sinit_max_init_timeo);

	/* Set the local window size for receive.
	 * This is also the rcvbuf space per association.
	 * RFC 6 - A SCTP receiver MUST be able to receive a minimum of
	 * 1500 bytes in one SCTP packet.
	 */
	if ((sk->sk_rcvbuf/2) < SCTP_DEFAULT_MINWINDOW)
		asoc->rwnd = SCTP_DEFAULT_MINWINDOW;
	else
		asoc->rwnd = sk->sk_rcvbuf/2;

	asoc->a_rwnd = asoc->rwnd;

	/* Use my own max window until I learn something better.  */
	asoc->peer.rwnd = SCTP_DEFAULT_MAXWINDOW;

	/* Initialize the receive memory counter */
	atomic_set(&asoc->rmem_alloc, 0);

	init_waitqueue_head(&asoc->wait);

	asoc->c.my_vtag = sctp_generate_tag(ep);
	asoc->c.my_port = ep->base.bind_addr.port;

	asoc->c.initial_tsn = sctp_generate_tsn(ep);

	asoc->next_tsn = asoc->c.initial_tsn;

	asoc->ctsn_ack_point = asoc->next_tsn - 1;
	asoc->adv_peer_ack_point = asoc->ctsn_ack_point;
	asoc->highest_sacked = asoc->ctsn_ack_point;
	asoc->last_cwr_tsn = asoc->ctsn_ack_point;

	/* ADDIP Section 4.1 Asconf Chunk Procedures
	 *
	 * When an endpoint has an ASCONF signaled change to be sent to the
	 * remote endpoint it should do the following:
	 * ...
	 * A2) a serial number should be assigned to the chunk. The serial
	 * number SHOULD be a monotonically increasing number. The serial
	 * numbers SHOULD be initialized at the start of the
	 * association to the same value as the initial TSN.
	 */
	asoc->addip_serial = asoc->c.initial_tsn;
	asoc->strreset_outseq = asoc->c.initial_tsn;

	INIT_LIST_HEAD(&asoc->addip_chunk_list);
	INIT_LIST_HEAD(&asoc->asconf_ack_list);

	/* Make an empty list of remote transport addresses.  */
	INIT_LIST_HEAD(&asoc->peer.transport_addr_list);

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * After the reception of the first data chunk in an
	 * association the endpoint must immediately respond with a
	 * sack to acknowledge the data chunk.  Subsequent
	 * acknowledgements should be done as described in Section
	 * 6.2.
	 *
	 * [We implement this by telling a new association that it
	 * already received one packet.]
	 */
	asoc->peer.sack_needed = 1;
	asoc->peer.sack_generation = 1;

	/* Create an input queue.  */
	sctp_inq_init(&asoc->base.inqueue);
	sctp_inq_set_th_handler(&asoc->base.inqueue, sctp_assoc_bh_rcv);

	/* Create an output queue.  */
	sctp_outq_init(asoc, &asoc->outqueue);

	if (!sctp_ulpq_init(&asoc->ulpq, asoc))
		goto fail_init;

	if (sctp_stream_init(&asoc->stream, asoc->c.sinit_num_ostreams,
			     0, gfp))
		goto fail_init;

	/* Initialize default path MTU. */
	asoc->pathmtu = sp->pathmtu;
	sctp_assoc_update_frag_point(asoc);

	/* Assume that peer would support both address types unless we are
	 * told otherwise.
	 */
	asoc->peer.ipv4_address = 1;
	if (asoc->base.sk->sk_family == PF_INET6)
		asoc->peer.ipv6_address = 1;
	INIT_LIST_HEAD(&asoc->asocs);

	asoc->default_stream = sp->default_stream;
	asoc->default_ppid = sp->default_ppid;
	asoc->default_flags = sp->default_flags;
	asoc->default_context = sp->default_context;
	asoc->default_timetolive = sp->default_timetolive;
	asoc->default_rcv_context = sp->default_rcv_context;

	/* AUTH related initializations */
	INIT_LIST_HEAD(&asoc->endpoint_shared_keys);
	if (sctp_auth_asoc_copy_shkeys(ep, asoc, gfp))
		goto stream_free;

	asoc->active_key_id = ep->active_key_id;
	asoc->strreset_enable = ep->strreset_enable;

	/* Save the hmacs and chunks list into this association */
	if (ep->auth_hmacs_list)
		memcpy(asoc->c.auth_hmacs, ep->auth_hmacs_list,
			ntohs(ep->auth_hmacs_list->param_hdr.length));
	if (ep->auth_chunk_list)
		memcpy(asoc->c.auth_chunks, ep->auth_chunk_list,
			ntohs(ep->auth_chunk_list->param_hdr.length));

	/* Get the AUTH random number for this association */
	p = (struct sctp_paramhdr *)asoc->c.auth_random;
	p->type = SCTP_PARAM_RANDOM;
	p->length = htons(sizeof(*p) + SCTP_AUTH_RANDOM_LENGTH);
	get_random_bytes(p+1, SCTP_AUTH_RANDOM_LENGTH);

	return asoc;

stream_free:
	sctp_stream_free(&asoc->stream);
fail_init:
	sock_put(asoc->base.sk);
	sctp_endpoint_put(asoc->ep);
	return NULL;
}