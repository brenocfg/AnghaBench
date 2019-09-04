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
typedef  scalar_t__ uint ;
struct xfs_rui_log_format {int /*<<< orphan*/  rui_nextents; } ;
struct xfs_log_iovec {scalar_t__ i_len; struct xfs_rui_log_format* i_addr; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  memcpy (struct xfs_rui_log_format*,struct xfs_rui_log_format*,scalar_t__) ; 
 scalar_t__ xfs_rui_log_format_sizeof (int /*<<< orphan*/ ) ; 

int
xfs_rui_copy_format(
	struct xfs_log_iovec		*buf,
	struct xfs_rui_log_format	*dst_rui_fmt)
{
	struct xfs_rui_log_format	*src_rui_fmt;
	uint				len;

	src_rui_fmt = buf->i_addr;
	len = xfs_rui_log_format_sizeof(src_rui_fmt->rui_nextents);

	if (buf->i_len != len)
		return -EFSCORRUPTED;

	memcpy(dst_rui_fmt, src_rui_fmt, len);
	return 0;
}