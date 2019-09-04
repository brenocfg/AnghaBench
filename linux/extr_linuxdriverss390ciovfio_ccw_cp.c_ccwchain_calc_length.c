#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {scalar_t__ i2k; int /*<<< orphan*/  c64; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct channel_program {TYPE_2__ orb; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int CCWCHAIN_LEN_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ccw_is_chain (struct ccw1*) ; 
 scalar_t__ ccw_is_idal (struct ccw1*) ; 
 int /*<<< orphan*/  ccw_is_tic (struct ccw1*) ; 
 int copy_ccw_from_iova (struct channel_program*,struct ccw1*,int /*<<< orphan*/ ,int) ; 
 struct ccw1* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ccw1*) ; 

__attribute__((used)) static int ccwchain_calc_length(u64 iova, struct channel_program *cp)
{
	struct ccw1 *ccw, *p;
	int cnt;

	/*
	 * Copy current chain from guest to host kernel.
	 * Currently the chain length is limited to CCWCHAIN_LEN_MAX (256).
	 * So copying 2K is enough (safe).
	 */
	p = ccw = kcalloc(CCWCHAIN_LEN_MAX, sizeof(*ccw), GFP_KERNEL);
	if (!ccw)
		return -ENOMEM;

	cnt = copy_ccw_from_iova(cp, ccw, iova, CCWCHAIN_LEN_MAX);
	if (cnt) {
		kfree(ccw);
		return cnt;
	}

	cnt = 0;
	do {
		cnt++;

		/*
		 * As we don't want to fail direct addressing even if the
		 * orb specified one of the unsupported formats, we defer
		 * checking for IDAWs in unsupported formats to here.
		 */
		if ((!cp->orb.cmd.c64 || cp->orb.cmd.i2k) && ccw_is_idal(ccw)) {
			kfree(p);
			return -EOPNOTSUPP;
		}

		if ((!ccw_is_chain(ccw)) && (!ccw_is_tic(ccw)))
			break;

		ccw++;
	} while (cnt < CCWCHAIN_LEN_MAX + 1);

	if (cnt == CCWCHAIN_LEN_MAX + 1)
		cnt = -EINVAL;

	kfree(p);
	return cnt;
}