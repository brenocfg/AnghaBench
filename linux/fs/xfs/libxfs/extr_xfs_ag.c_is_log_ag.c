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
struct TYPE_2__ {scalar_t__ sb_logstart; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct aghdr_init_data {scalar_t__ agno; } ;

/* Variables and functions */
 scalar_t__ XFS_FSB_TO_AGNO (struct xfs_mount*,scalar_t__) ; 

__attribute__((used)) static inline bool is_log_ag(struct xfs_mount *mp, struct aghdr_init_data *id)
{
	return mp->m_sb.sb_logstart > 0 &&
	       id->agno == XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart);
}