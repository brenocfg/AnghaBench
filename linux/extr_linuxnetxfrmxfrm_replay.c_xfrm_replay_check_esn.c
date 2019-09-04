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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  replay; int /*<<< orphan*/  replay_window; } ;
struct xfrm_state {TYPE_1__ stats; struct xfrm_replay_state_esn* replay_esn; } ;
struct xfrm_replay_state_esn {int replay_window; int seq; scalar_t__ seq_hi; unsigned int* bmp; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ likely (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm_audit_state_replay (struct xfrm_state*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_replay_check_esn(struct xfrm_state *x,
				 struct sk_buff *skb, __be32 net_seq)
{
	unsigned int bitnr, nr;
	u32 diff;
	struct xfrm_replay_state_esn *replay_esn = x->replay_esn;
	u32 pos;
	u32 seq = ntohl(net_seq);
	u32 wsize = replay_esn->replay_window;
	u32 top = replay_esn->seq;
	u32 bottom = top - wsize + 1;

	if (!wsize)
		return 0;

	if (unlikely(seq == 0 && replay_esn->seq_hi == 0 &&
		     (replay_esn->seq < replay_esn->replay_window - 1)))
		goto err;

	diff = top - seq;

	if (likely(top >= wsize - 1)) {
		/* A. same subspace */
		if (likely(seq > top) || seq < bottom)
			return 0;
	} else {
		/* B. window spans two subspaces */
		if (likely(seq > top && seq < bottom))
			return 0;
		if (seq >= bottom)
			diff = ~seq + top + 1;
	}

	if (diff >= replay_esn->replay_window) {
		x->stats.replay_window++;
		goto err;
	}

	pos = (replay_esn->seq - 1) % replay_esn->replay_window;

	if (pos >= diff)
		bitnr = (pos - diff) % replay_esn->replay_window;
	else
		bitnr = replay_esn->replay_window - (diff - pos);

	nr = bitnr >> 5;
	bitnr = bitnr & 0x1F;
	if (replay_esn->bmp[nr] & (1U << bitnr))
		goto err_replay;

	return 0;

err_replay:
	x->stats.replay++;
err:
	xfrm_audit_state_replay(x, skb, net_seq);
	return -EINVAL;
}