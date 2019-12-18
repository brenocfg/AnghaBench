#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ count; scalar_t__ offset; } ;
struct nfs_pgio_header {TYPE_2__ args; TYPE_1__* inode; int /*<<< orphan*/  pages; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  filemap_fdatawrite_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nfs_async_write_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_async_write_reschedule_io(struct nfs_pgio_header *hdr)
{
	nfs_async_write_error(&hdr->pages, 0);
	filemap_fdatawrite_range(hdr->inode->i_mapping, hdr->args.offset,
			hdr->args.offset + hdr->args.count - 1);
}