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
struct xfs_ioend {int /*<<< orphan*/ * io_append_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  xfs_setfilesize_ioend (struct xfs_ioend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_ioend_merge_append_transactions(
	struct xfs_ioend	*ioend,
	struct xfs_ioend	*next)
{
	if (!ioend->io_append_trans) {
		ioend->io_append_trans = next->io_append_trans;
		next->io_append_trans = NULL;
	} else {
		xfs_setfilesize_ioend(next, -ECANCELED);
	}
}