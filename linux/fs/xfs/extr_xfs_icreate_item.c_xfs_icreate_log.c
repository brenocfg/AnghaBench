#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int xfs_agnumber_t ;
typedef  unsigned int xfs_agblock_t ;
struct xfs_trans {int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_mountp; } ;
struct TYPE_5__ {int /*<<< orphan*/  li_flags; } ;
struct TYPE_4__ {int icl_size; void* icl_gen; void* icl_length; void* icl_isize; void* icl_count; void* icl_agbno; void* icl_ag; int /*<<< orphan*/  icl_type; } ;
struct xfs_icreate_item {TYPE_2__ ic_item; TYPE_1__ ic_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_LI_ICREATE ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 void* cpu_to_be32 (unsigned int) ; 
 struct xfs_icreate_item* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_icreate_item_ops ; 
 int /*<<< orphan*/  xfs_icreate_zone ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_add_item (struct xfs_trans*,TYPE_2__*) ; 

void
xfs_icreate_log(
	struct xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	unsigned int		count,
	unsigned int		inode_size,
	xfs_agblock_t		length,
	unsigned int		generation)
{
	struct xfs_icreate_item	*icp;

	icp = kmem_zone_zalloc(xfs_icreate_zone, 0);

	xfs_log_item_init(tp->t_mountp, &icp->ic_item, XFS_LI_ICREATE,
			  &xfs_icreate_item_ops);

	icp->ic_format.icl_type = XFS_LI_ICREATE;
	icp->ic_format.icl_size = 1;	/* single vector */
	icp->ic_format.icl_ag = cpu_to_be32(agno);
	icp->ic_format.icl_agbno = cpu_to_be32(agbno);
	icp->ic_format.icl_count = cpu_to_be32(count);
	icp->ic_format.icl_isize = cpu_to_be32(inode_size);
	icp->ic_format.icl_length = cpu_to_be32(length);
	icp->ic_format.icl_gen = cpu_to_be32(generation);

	xfs_trans_add_item(tp, &icp->ic_item);
	tp->t_flags |= XFS_TRANS_DIRTY;
	set_bit(XFS_LI_DIRTY, &icp->ic_item.li_flags);
}