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
struct TYPE_2__ {int sb_inodelog; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_dinode {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 struct xfs_dinode* xfs_buf_offset (struct xfs_buf*,int) ; 

__attribute__((used)) static inline struct xfs_dinode *
xfs_make_iptr(struct xfs_mount *mp, struct xfs_buf *b, int o)
{
	return xfs_buf_offset(b, o << (mp)->m_sb.sb_inodelog);
}