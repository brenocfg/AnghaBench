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
struct TYPE_2__ {int flags; } ;
struct xfrm_state {int /*<<< orphan*/ * repl; TYPE_1__ props; struct xfrm_replay_state_esn* replay_esn; } ;
struct xfrm_replay_state_esn {int replay_window; int bmp_len; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  xfrm_replay_bmp ; 
 int /*<<< orphan*/  xfrm_replay_esn ; 
 int /*<<< orphan*/  xfrm_replay_legacy ; 

int xfrm_init_replay(struct xfrm_state *x)
{
	struct xfrm_replay_state_esn *replay_esn = x->replay_esn;

	if (replay_esn) {
		if (replay_esn->replay_window >
		    replay_esn->bmp_len * sizeof(__u32) * 8)
			return -EINVAL;

		if (x->props.flags & XFRM_STATE_ESN) {
			if (replay_esn->replay_window == 0)
				return -EINVAL;
			x->repl = &xfrm_replay_esn;
		} else {
			x->repl = &xfrm_replay_bmp;
		}
	} else {
		x->repl = &xfrm_replay_legacy;
	}

	return 0;
}