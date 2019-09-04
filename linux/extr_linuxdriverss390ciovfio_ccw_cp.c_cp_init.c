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
struct TYPE_4__ {int /*<<< orphan*/  pfch; int /*<<< orphan*/  cpa; } ;
union orb {TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;
struct TYPE_5__ {int c64; } ;
struct TYPE_6__ {TYPE_2__ cmd; } ;
struct channel_program {TYPE_3__ orb; struct device* mdev; int /*<<< orphan*/  ccwchain_list; } ;
struct ccwchain {int /*<<< orphan*/  ch_ccw; int /*<<< orphan*/  ch_iova; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ccwchain* ccwchain_alloc (struct channel_program*,int) ; 
 int ccwchain_calc_length (int /*<<< orphan*/ ,struct channel_program*) ; 
 int /*<<< orphan*/  ccwchain_free (struct ccwchain*) ; 
 int ccwchain_loop_tic (struct ccwchain*,struct channel_program*) ; 
 int copy_ccw_from_iova (struct channel_program*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_unpin_free (struct channel_program*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,union orb*,int) ; 

int cp_init(struct channel_program *cp, struct device *mdev, union orb *orb)
{
	u64 iova = orb->cmd.cpa;
	struct ccwchain *chain;
	int len, ret;

	/*
	 * XXX:
	 * Only support prefetch enable mode now.
	 */
	if (!orb->cmd.pfch)
		return -EOPNOTSUPP;

	INIT_LIST_HEAD(&cp->ccwchain_list);
	memcpy(&cp->orb, orb, sizeof(*orb));
	cp->mdev = mdev;

	/* Get chain length. */
	len = ccwchain_calc_length(iova, cp);
	if (len < 0)
		return len;

	/* Alloc mem for the head chain. */
	chain = ccwchain_alloc(cp, len);
	if (!chain)
		return -ENOMEM;
	chain->ch_iova = iova;

	/* Copy the head chain from guest. */
	ret = copy_ccw_from_iova(cp, chain->ch_ccw, iova, len);
	if (ret) {
		ccwchain_free(chain);
		return ret;
	}

	/* Now loop for its TICs. */
	ret = ccwchain_loop_tic(chain, cp);
	if (ret)
		cp_unpin_free(cp);
	/* It is safe to force: if not set but idals used
	 * ccwchain_calc_length returns an error.
	 */
	cp->orb.cmd.c64 = 1;

	return ret;
}