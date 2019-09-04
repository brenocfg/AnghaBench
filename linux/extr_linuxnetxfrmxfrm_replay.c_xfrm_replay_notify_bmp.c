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
struct xfrm_state {int xflags; scalar_t__ replay_maxage; int /*<<< orphan*/  rtimer; struct xfrm_replay_state_esn* replay_esn; struct xfrm_replay_state_esn* preplay_esn; scalar_t__ replay_maxdiff; } ;
struct xfrm_replay_state_esn {scalar_t__ oseq; scalar_t__ seq; } ;
struct TYPE_2__ {int aevent; } ;
struct km_event {TYPE_1__ data; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_MSG_NEWAE ; 
#define  XFRM_REPLAY_TIMEOUT 129 
#define  XFRM_REPLAY_UPDATE 128 
 int XFRM_TIME_DEFER ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  km_state_notify (struct xfrm_state*,struct km_event*) ; 
 int /*<<< orphan*/  memcmp (struct xfrm_replay_state_esn*,struct xfrm_replay_state_esn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfrm_replay_state_esn*,struct xfrm_replay_state_esn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xfrm_replay_state_esn_len (struct xfrm_replay_state_esn*) ; 

__attribute__((used)) static void xfrm_replay_notify_bmp(struct xfrm_state *x, int event)
{
	struct km_event c;
	struct xfrm_replay_state_esn *replay_esn = x->replay_esn;
	struct xfrm_replay_state_esn *preplay_esn = x->preplay_esn;

	/* we send notify messages in case
	 *  1. we updated on of the sequence numbers, and the seqno difference
	 *     is at least x->replay_maxdiff, in this case we also update the
	 *     timeout of our timer function
	 *  2. if x->replay_maxage has elapsed since last update,
	 *     and there were changes
	 *
	 *  The state structure must be locked!
	 */

	switch (event) {
	case XFRM_REPLAY_UPDATE:
		if (!x->replay_maxdiff ||
		    ((replay_esn->seq - preplay_esn->seq < x->replay_maxdiff) &&
		    (replay_esn->oseq - preplay_esn->oseq
		     < x->replay_maxdiff))) {
			if (x->xflags & XFRM_TIME_DEFER)
				event = XFRM_REPLAY_TIMEOUT;
			else
				return;
		}

		break;

	case XFRM_REPLAY_TIMEOUT:
		if (memcmp(x->replay_esn, x->preplay_esn,
			   xfrm_replay_state_esn_len(replay_esn)) == 0) {
			x->xflags |= XFRM_TIME_DEFER;
			return;
		}

		break;
	}

	memcpy(x->preplay_esn, x->replay_esn,
	       xfrm_replay_state_esn_len(replay_esn));
	c.event = XFRM_MSG_NEWAE;
	c.data.aevent = event;
	km_state_notify(x, &c);

	if (x->replay_maxage &&
	    !mod_timer(&x->rtimer, jiffies + x->replay_maxage))
		x->xflags &= ~XFRM_TIME_DEFER;
}