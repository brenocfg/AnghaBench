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
struct nfs4_ff_io_stat {int /*<<< orphan*/  bytes_requested; int /*<<< orphan*/  ops_requested; } ;
struct nfs4_ff_layoutstat {struct nfs4_ff_io_stat io_stat; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */

__attribute__((used)) static void
nfs4_ff_layout_stat_io_update_requested(struct nfs4_ff_layoutstat *layoutstat,
		__u64 requested)
{
	struct nfs4_ff_io_stat *iostat = &layoutstat->io_stat;

	iostat->ops_requested++;
	iostat->bytes_requested += requested;
}