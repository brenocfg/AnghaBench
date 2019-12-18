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
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_PTAG_ERROR_REPORT ; 
 int /*<<< orphan*/  xfs_alert_tag (struct xfs_mount*,int /*<<< orphan*/ ,char*,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 int xfs_error_level ; 
 int /*<<< orphan*/  xfs_stack_trace () ; 

void
xfs_error_report(
	const char		*tag,
	int			level,
	struct xfs_mount	*mp,
	const char		*filename,
	int			linenum,
	xfs_failaddr_t		failaddr)
{
	if (level <= xfs_error_level) {
		xfs_alert_tag(mp, XFS_PTAG_ERROR_REPORT,
		"Internal error %s at line %d of file %s.  Caller %pS",
			    tag, linenum, filename, failaddr);

		xfs_stack_trace();
	}
}