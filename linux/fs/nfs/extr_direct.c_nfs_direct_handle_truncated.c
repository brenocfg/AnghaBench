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
struct nfs_pgio_header {scalar_t__ error; int /*<<< orphan*/  flags; } ;
struct nfs_direct_req {scalar_t__ max_count; scalar_t__ count; scalar_t__ error; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_EOF ; 
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs_direct_handle_truncated(struct nfs_direct_req *dreq,
			    const struct nfs_pgio_header *hdr,
			    ssize_t dreq_len)
{
	if (!(test_bit(NFS_IOHDR_ERROR, &hdr->flags) ||
	      test_bit(NFS_IOHDR_EOF, &hdr->flags)))
		return;
	if (dreq->max_count >= dreq_len) {
		dreq->max_count = dreq_len;
		if (dreq->count > dreq_len)
			dreq->count = dreq_len;

		if (test_bit(NFS_IOHDR_ERROR, &hdr->flags))
			dreq->error = hdr->error;
		else /* Clear outstanding error if this is EOF */
			dreq->error = 0;
	}
}