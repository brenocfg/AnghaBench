#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tk_status; } ;
struct nfs_pgio_header {TYPE_2__ task; int /*<<< orphan*/  flags; int /*<<< orphan*/  inode; int /*<<< orphan*/  pnfs_error; } ;
struct TYPE_6__ {TYPE_1__* pnfs_curr_ld; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 TYPE_3__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int PNFS_LAYOUTRET_ON_ERROR ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_return_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_write_done_resend_to_mds (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pnfs_ld_handle_write_error(struct nfs_pgio_header *hdr)
{

	dprintk("pnfs write error = %d\n", hdr->pnfs_error);
	if (NFS_SERVER(hdr->inode)->pnfs_curr_ld->flags &
	    PNFS_LAYOUTRET_ON_ERROR) {
		pnfs_return_layout(hdr->inode);
	}
	if (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags))
		hdr->task.tk_status = pnfs_write_done_resend_to_mds(hdr);
}