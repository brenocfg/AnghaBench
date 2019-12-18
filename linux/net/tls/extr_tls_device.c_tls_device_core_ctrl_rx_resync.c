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
typedef  int /*<<< orphan*/  u8 ;
struct tls_prot_info {int /*<<< orphan*/  rec_seq_size; } ;
struct TYPE_4__ {int decrypted_failed; int decrypted_tgt; } ;
struct tls_offload_context_rx {scalar_t__ resync_type; int resync_nh_do_now; TYPE_1__ resync_nh; scalar_t__ resync_nh_reset; } ;
struct TYPE_5__ {int /*<<< orphan*/  rec_seq; } ;
struct tls_context {TYPE_2__ rx; struct tls_prot_info prot_info; } ;
struct strp_msg {scalar_t__ full_len; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  copied_seq; } ;

/* Variables and functions */
 int TLS_DEVICE_RESYNC_NH_MAX_IVAL ; 
 int TLS_DEVICE_RESYNC_NH_START_IVAL ; 
 int TLS_MAX_REC_SEQ_SIZE ; 
 scalar_t__ TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 
 scalar_t__ tcp_inq (struct sock*) ; 
 TYPE_3__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tls_bigint_increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_device_resync_rx (struct tls_context*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tls_device_core_ctrl_rx_resync(struct tls_context *tls_ctx,
					   struct tls_offload_context_rx *ctx,
					   struct sock *sk, struct sk_buff *skb)
{
	struct strp_msg *rxm;

	/* device will request resyncs by itself based on stream scan */
	if (ctx->resync_type != TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT)
		return;
	/* already scheduled */
	if (ctx->resync_nh_do_now)
		return;
	/* seen decrypted fragments since last fully-failed record */
	if (ctx->resync_nh_reset) {
		ctx->resync_nh_reset = 0;
		ctx->resync_nh.decrypted_failed = 1;
		ctx->resync_nh.decrypted_tgt = TLS_DEVICE_RESYNC_NH_START_IVAL;
		return;
	}

	if (++ctx->resync_nh.decrypted_failed <= ctx->resync_nh.decrypted_tgt)
		return;

	/* doing resync, bump the next target in case it fails */
	if (ctx->resync_nh.decrypted_tgt < TLS_DEVICE_RESYNC_NH_MAX_IVAL)
		ctx->resync_nh.decrypted_tgt *= 2;
	else
		ctx->resync_nh.decrypted_tgt += TLS_DEVICE_RESYNC_NH_MAX_IVAL;

	rxm = strp_msg(skb);

	/* head of next rec is already in, parser will sync for us */
	if (tcp_inq(sk) > rxm->full_len) {
		ctx->resync_nh_do_now = 1;
	} else {
		struct tls_prot_info *prot = &tls_ctx->prot_info;
		u8 rcd_sn[TLS_MAX_REC_SEQ_SIZE];

		memcpy(rcd_sn, tls_ctx->rx.rec_seq, prot->rec_seq_size);
		tls_bigint_increment(rcd_sn, prot->rec_seq_size);

		tls_device_resync_rx(tls_ctx, sk, tcp_sk(sk)->copied_seq,
				     rcd_sn);
	}
}