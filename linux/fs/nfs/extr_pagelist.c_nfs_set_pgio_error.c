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
struct nfs_pgio_header {unsigned int io_start; unsigned int good_bytes; int error; int /*<<< orphan*/  flags; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_EOF ; 
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs_set_pgio_error(struct nfs_pgio_header *hdr, int error, loff_t pos)
{
	unsigned int new = pos - hdr->io_start;

	if (hdr->good_bytes > new) {
		hdr->good_bytes = new;
		clear_bit(NFS_IOHDR_EOF, &hdr->flags);
		if (!test_and_set_bit(NFS_IOHDR_ERROR, &hdr->flags))
			hdr->error = error;
	}
}