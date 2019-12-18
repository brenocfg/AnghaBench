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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  scalar_t__ xfs_agino_t ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 scalar_t__ NULLAGINO ; 
 scalar_t__ xfs_verify_agino (struct xfs_mount*,int /*<<< orphan*/ ,scalar_t__) ; 

bool
xfs_verify_agino_or_null(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino)
{
	return agino == NULLAGINO || xfs_verify_agino(mp, agno, agino);
}