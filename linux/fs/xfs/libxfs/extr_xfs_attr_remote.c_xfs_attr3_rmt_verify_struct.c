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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int __xfs_attr3_rmt_read_verify (struct xfs_buf*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_attr3_rmt_verify_struct(
	struct xfs_buf	*bp)
{
	xfs_failaddr_t	fa;
	int		error;

	error = __xfs_attr3_rmt_read_verify(bp, false, &fa);
	return error ? fa : NULL;
}