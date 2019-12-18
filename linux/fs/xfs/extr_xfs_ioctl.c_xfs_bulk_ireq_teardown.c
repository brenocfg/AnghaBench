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
struct xfs_ibulk {int /*<<< orphan*/  ocount; int /*<<< orphan*/  startino; } ;
struct xfs_bulk_ireq {int /*<<< orphan*/  ocount; int /*<<< orphan*/  ino; } ;

/* Variables and functions */

__attribute__((used)) static void
xfs_bulk_ireq_teardown(
	struct xfs_bulk_ireq	*hdr,
	struct xfs_ibulk	*breq)
{
	hdr->ino = breq->startino;
	hdr->ocount = breq->ocount;
}