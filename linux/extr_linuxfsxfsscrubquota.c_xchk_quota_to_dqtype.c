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
typedef  int /*<<< orphan*/  uint ;
struct xfs_scrub {TYPE_1__* sm; } ;
struct TYPE_2__ {int sm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DQ_GROUP ; 
 int /*<<< orphan*/  XFS_DQ_PROJ ; 
 int /*<<< orphan*/  XFS_DQ_USER ; 
#define  XFS_SCRUB_TYPE_GQUOTA 130 
#define  XFS_SCRUB_TYPE_PQUOTA 129 
#define  XFS_SCRUB_TYPE_UQUOTA 128 

__attribute__((used)) static inline uint
xchk_quota_to_dqtype(
	struct xfs_scrub	*sc)
{
	switch (sc->sm->sm_type) {
	case XFS_SCRUB_TYPE_UQUOTA:
		return XFS_DQ_USER;
	case XFS_SCRUB_TYPE_GQUOTA:
		return XFS_DQ_GROUP;
	case XFS_SCRUB_TYPE_PQUOTA:
		return XFS_DQ_PROJ;
	default:
		return 0;
	}
}