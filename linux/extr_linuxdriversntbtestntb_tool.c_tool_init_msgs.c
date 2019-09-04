#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tool_ctx {int inmsg_cnt; int peer_cnt; TYPE_3__* peers; TYPE_4__* ntb; TYPE_1__* inmsgs; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int outmsg_cnt; TYPE_2__* outmsgs; } ;
struct TYPE_6__ {int midx; int pidx; struct tool_ctx* tc; } ;
struct TYPE_5__ {int midx; int pidx; struct tool_ctx* tc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 void* ntb_msg_count (TYPE_4__*) ; 

__attribute__((used)) static int tool_init_msgs(struct tool_ctx *tc)
{
	int midx, pidx;

	/* Initialize inbound message structures */
	tc->inmsg_cnt = ntb_msg_count(tc->ntb);
	tc->inmsgs = devm_kcalloc(&tc->ntb->dev, tc->inmsg_cnt,
				   sizeof(*tc->inmsgs), GFP_KERNEL);
	if (tc->inmsgs == NULL)
		return -ENOMEM;

	for (midx = 0; midx < tc->inmsg_cnt; midx++) {
		tc->inmsgs[midx].midx = midx;
		tc->inmsgs[midx].pidx = -1;
		tc->inmsgs[midx].tc = tc;
	}

	/* Initialize outbound message structures */
	for (pidx = 0; pidx < tc->peer_cnt; pidx++) {
		tc->peers[pidx].outmsg_cnt = ntb_msg_count(tc->ntb);
		tc->peers[pidx].outmsgs =
			devm_kcalloc(&tc->ntb->dev, tc->peers[pidx].outmsg_cnt,
				sizeof(*tc->peers[pidx].outmsgs), GFP_KERNEL);
		if (tc->peers[pidx].outmsgs == NULL)
			return -ENOMEM;

		for (midx = 0; midx < tc->peers[pidx].outmsg_cnt; midx++) {
			tc->peers[pidx].outmsgs[midx].midx = midx;
			tc->peers[pidx].outmsgs[midx].pidx = pidx;
			tc->peers[pidx].outmsgs[midx].tc = tc;
		}
	}

	return 0;
}