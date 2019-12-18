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
struct nfs_pgio_header {scalar_t__ io_start; scalar_t__ good_bytes; } ;
struct nfs_direct_req {scalar_t__ io_start; scalar_t__ max_count; scalar_t__ count; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_direct_handle_truncated (struct nfs_direct_req*,struct nfs_pgio_header const*,scalar_t__) ; 

__attribute__((used)) static void
nfs_direct_count_bytes(struct nfs_direct_req *dreq,
		       const struct nfs_pgio_header *hdr)
{
	loff_t hdr_end = hdr->io_start + hdr->good_bytes;
	ssize_t dreq_len = 0;

	if (hdr_end > dreq->io_start)
		dreq_len = hdr_end - dreq->io_start;

	nfs_direct_handle_truncated(dreq, hdr, dreq_len);

	if (dreq_len > dreq->max_count)
		dreq_len = dreq->max_count;

	if (dreq->count < dreq_len)
		dreq->count = dreq_len;
}