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
 int /*<<< orphan*/  xfs_alert (struct xfs_mount*,char*) ; 
 int xfs_error_level ; 
 int /*<<< orphan*/  xfs_error_report (char const*,int,struct xfs_mount*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_hex_dump (void*,size_t) ; 

void
xfs_corruption_error(
	const char		*tag,
	int			level,
	struct xfs_mount	*mp,
	void			*buf,
	size_t			bufsize,
	const char		*filename,
	int			linenum,
	xfs_failaddr_t		failaddr)
{
	if (level <= xfs_error_level)
		xfs_hex_dump(buf, bufsize);
	xfs_error_report(tag, level, mp, filename, linenum, failaddr);
	xfs_alert(mp, "Corruption detected. Unmount and run xfs_repair");
}