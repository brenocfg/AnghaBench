#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct z_erofs_unzip_io {int /*<<< orphan*/  pending_bios; TYPE_1__ u; } ;
struct z_erofs_collector {int /*<<< orphan*/  owned_head; } ;
struct super_block {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 size_t JQ_BYPASS ; 
 size_t JQ_SUBMIT ; 
 int NR_JOBQUEUES ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z_erofs_vle_submit_all (struct super_block*,int /*<<< orphan*/ ,struct list_head*,struct z_erofs_unzip_io*,int) ; 
 int /*<<< orphan*/  z_erofs_vle_unzip_all (struct super_block*,struct z_erofs_unzip_io*,struct list_head*) ; 

__attribute__((used)) static void z_erofs_submit_and_unzip(struct super_block *sb,
				     struct z_erofs_collector *clt,
				     struct list_head *pagepool,
				     bool force_fg)
{
	struct z_erofs_unzip_io io[NR_JOBQUEUES];

	if (!z_erofs_vle_submit_all(sb, clt->owned_head,
				    pagepool, io, force_fg))
		return;

	/* decompress no I/O pclusters immediately */
	z_erofs_vle_unzip_all(sb, &io[JQ_BYPASS], pagepool);

	if (!force_fg)
		return;

	/* wait until all bios are completed */
	wait_event(io[JQ_SUBMIT].u.wait,
		   !atomic_read(&io[JQ_SUBMIT].pending_bios));

	/* let's synchronous decompression */
	z_erofs_vle_unzip_all(sb, &io[JQ_SUBMIT], pagepool);
}