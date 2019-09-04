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
struct nfs_pgio_header {size_t pgio_mirror_idx; scalar_t__ good_bytes; scalar_t__ io_start; } ;
struct nfs_direct_req {scalar_t__ count; scalar_t__ max_count; int mirror_count; scalar_t__ io_start; TYPE_1__* mirrors; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
nfs_direct_good_bytes(struct nfs_direct_req *dreq, struct nfs_pgio_header *hdr)
{
	int i;
	ssize_t count;

	WARN_ON_ONCE(dreq->count >= dreq->max_count);

	if (dreq->mirror_count == 1) {
		dreq->mirrors[hdr->pgio_mirror_idx].count += hdr->good_bytes;
		dreq->count += hdr->good_bytes;
	} else {
		/* mirrored writes */
		count = dreq->mirrors[hdr->pgio_mirror_idx].count;
		if (count + dreq->io_start < hdr->io_start + hdr->good_bytes) {
			count = hdr->io_start + hdr->good_bytes - dreq->io_start;
			dreq->mirrors[hdr->pgio_mirror_idx].count = count;
		}
		/* update the dreq->count by finding the minimum agreed count from all
		 * mirrors */
		count = dreq->mirrors[0].count;

		for (i = 1; i < dreq->mirror_count; i++)
			count = min(count, dreq->mirrors[i].count);

		dreq->count = count;
	}
}