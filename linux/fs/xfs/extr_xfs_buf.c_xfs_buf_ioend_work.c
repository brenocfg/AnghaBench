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
struct xfs_buf {int dummy; } ;
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b_ioend_work ; 
 struct xfs_buf* container_of (struct work_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_ioend (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_t ; 

__attribute__((used)) static void
xfs_buf_ioend_work(
	struct work_struct	*work)
{
	struct xfs_buf		*bp =
		container_of(work, xfs_buf_t, b_ioend_work);

	xfs_buf_ioend(bp);
}