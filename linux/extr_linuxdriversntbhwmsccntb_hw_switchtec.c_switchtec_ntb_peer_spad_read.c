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
typedef  int /*<<< orphan*/  u32 ;
struct switchtec_ntb {TYPE_1__* peer_shared; } ;
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * spad; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int NTB_DEF_PEER_IDX ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 

__attribute__((used)) static u32 switchtec_ntb_peer_spad_read(struct ntb_dev *ntb, int pidx,
					int sidx)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (pidx != NTB_DEF_PEER_IDX)
		return -EINVAL;

	if (sidx < 0 || sidx >= ARRAY_SIZE(sndev->peer_shared->spad))
		return 0;

	if (!sndev->peer_shared)
		return 0;

	return ioread32(&sndev->peer_shared->spad[sidx]);
}