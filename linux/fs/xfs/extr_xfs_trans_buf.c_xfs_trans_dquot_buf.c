#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_6__ {struct xfs_buf_log_item* b_log_item; } ;
typedef  TYPE_2__ xfs_buf_t ;
typedef  int uint ;
struct TYPE_5__ {int blf_flags; } ;
struct xfs_buf_log_item {TYPE_1__ __bli_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_BLFT_GDQUOT_BUF ; 
 int XFS_BLFT_PDQUOT_BUF ; 
 int XFS_BLFT_UDQUOT_BUF ; 
 int XFS_BLFT_UNKNOWN_BUF ; 
#define  XFS_BLF_GDQUOT_BUF 130 
#define  XFS_BLF_PDQUOT_BUF 129 
#define  XFS_BLF_UDQUOT_BUF 128 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

void
xfs_trans_dquot_buf(
	xfs_trans_t		*tp,
	xfs_buf_t		*bp,
	uint			type)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(type == XFS_BLF_UDQUOT_BUF ||
	       type == XFS_BLF_PDQUOT_BUF ||
	       type == XFS_BLF_GDQUOT_BUF);

	bip->__bli_format.blf_flags |= type;

	switch (type) {
	case XFS_BLF_UDQUOT_BUF:
		type = XFS_BLFT_UDQUOT_BUF;
		break;
	case XFS_BLF_PDQUOT_BUF:
		type = XFS_BLFT_PDQUOT_BUF;
		break;
	case XFS_BLF_GDQUOT_BUF:
		type = XFS_BLFT_GDQUOT_BUF;
		break;
	default:
		type = XFS_BLFT_UNKNOWN_BUF;
		break;
	}

	xfs_trans_buf_set_type(tp, bp, type);
}