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
typedef  unsigned int u32 ;
struct xfrm_state {TYPE_1__* repl; struct xfrm_replay_state_esn* replay_esn; } ;
struct xfrm_replay_state_esn {int replay_window; int seq; unsigned int* bmp; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* notify ) (struct xfrm_state*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_REPLAY_UPDATE ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_aevent_is_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static void xfrm_replay_advance_bmp(struct xfrm_state *x, __be32 net_seq)
{
	unsigned int bitnr, nr, i;
	u32 diff;
	struct xfrm_replay_state_esn *replay_esn = x->replay_esn;
	u32 seq = ntohl(net_seq);
	u32 pos;

	if (!replay_esn->replay_window)
		return;

	pos = (replay_esn->seq - 1) % replay_esn->replay_window;

	if (seq > replay_esn->seq) {
		diff = seq - replay_esn->seq;

		if (diff < replay_esn->replay_window) {
			for (i = 1; i < diff; i++) {
				bitnr = (pos + i) % replay_esn->replay_window;
				nr = bitnr >> 5;
				bitnr = bitnr & 0x1F;
				replay_esn->bmp[nr] &=  ~(1U << bitnr);
			}
		} else {
			nr = (replay_esn->replay_window - 1) >> 5;
			for (i = 0; i <= nr; i++)
				replay_esn->bmp[i] = 0;
		}

		bitnr = (pos + diff) % replay_esn->replay_window;
		replay_esn->seq = seq;
	} else {
		diff = replay_esn->seq - seq;

		if (pos >= diff)
			bitnr = (pos - diff) % replay_esn->replay_window;
		else
			bitnr = replay_esn->replay_window - (diff - pos);
	}

	nr = bitnr >> 5;
	bitnr = bitnr & 0x1F;
	replay_esn->bmp[nr] |= (1U << bitnr);

	if (xfrm_aevent_is_on(xs_net(x)))
		x->repl->notify(x, XFRM_REPLAY_UPDATE);
}