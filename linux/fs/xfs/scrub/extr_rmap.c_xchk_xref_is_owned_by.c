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
typedef  int /*<<< orphan*/  xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct xfs_scrub {int dummy; } ;
struct xfs_owner_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xchk_xref_check_owner (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_owner_info const*,int) ; 

void
xchk_xref_is_owned_by(
	struct xfs_scrub		*sc,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	const struct xfs_owner_info	*oinfo)
{
	xchk_xref_check_owner(sc, bno, len, oinfo, true);
}