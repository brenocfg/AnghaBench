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
struct TYPE_3__ {int /*<<< orphan*/  fmt; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct channel_program {TYPE_2__ orb; int /*<<< orphan*/  mdev; } ;
struct ccw1 {int cmd_code; int /*<<< orphan*/  cda; scalar_t__ count; scalar_t__ flags; } ;
struct ccw0 {int cmd_code; int /*<<< orphan*/  cda; scalar_t__ count; scalar_t__ flags; } ;

/* Variables and functions */
 int CCW_CMD_TIC ; 
 int copy_from_iova (int /*<<< orphan*/ ,struct ccw1*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static long copy_ccw_from_iova(struct channel_program *cp,
			       struct ccw1 *to, u64 iova,
			       unsigned long len)
{
	struct ccw0 ccw0;
	struct ccw1 *pccw1;
	int ret;
	int i;

	ret = copy_from_iova(cp->mdev, to, iova, len * sizeof(struct ccw1));
	if (ret)
		return ret;

	if (!cp->orb.cmd.fmt) {
		pccw1 = to;
		for (i = 0; i < len; i++) {
			ccw0 = *(struct ccw0 *)pccw1;
			if ((pccw1->cmd_code & 0x0f) == CCW_CMD_TIC) {
				pccw1->cmd_code = CCW_CMD_TIC;
				pccw1->flags = 0;
				pccw1->count = 0;
			} else {
				pccw1->cmd_code = ccw0.cmd_code;
				pccw1->flags = ccw0.flags;
				pccw1->count = ccw0.count;
			}
			pccw1->cda = ccw0.cda;
			pccw1++;
		}
	}

	return ret;
}