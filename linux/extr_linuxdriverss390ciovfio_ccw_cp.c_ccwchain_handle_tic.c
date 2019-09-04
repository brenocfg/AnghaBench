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
struct channel_program {int dummy; } ;
struct ccwchain {int /*<<< orphan*/  ch_ccw; int /*<<< orphan*/  ch_iova; } ;
struct ccw1 {int /*<<< orphan*/  cda; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ccwchain* ccwchain_alloc (struct channel_program*,int) ; 
 int ccwchain_calc_length (int /*<<< orphan*/ ,struct channel_program*) ; 
 int /*<<< orphan*/  ccwchain_free (struct ccwchain*) ; 
 int ccwchain_loop_tic (struct ccwchain*,struct channel_program*) ; 
 int copy_ccw_from_iova (struct channel_program*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tic_target_chain_exists (struct ccw1*,struct channel_program*) ; 

__attribute__((used)) static int ccwchain_handle_tic(struct ccw1 *tic, struct channel_program *cp)
{
	struct ccwchain *chain;
	int len, ret;

	/* May transfer to an existing chain. */
	if (tic_target_chain_exists(tic, cp))
		return 0;

	/* Get chain length. */
	len = ccwchain_calc_length(tic->cda, cp);
	if (len < 0)
		return len;

	/* Need alloc a new chain for this one. */
	chain = ccwchain_alloc(cp, len);
	if (!chain)
		return -ENOMEM;
	chain->ch_iova = tic->cda;

	/* Copy the new chain from user. */
	ret = copy_ccw_from_iova(cp, chain->ch_ccw, tic->cda, len);
	if (ret) {
		ccwchain_free(chain);
		return ret;
	}

	/* Loop for tics on this new chain. */
	return ccwchain_loop_tic(chain, cp);
}