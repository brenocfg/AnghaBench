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
struct parallel_io {struct nfs_pgio_header* data; } ;
struct nfs_pgio_header {int /*<<< orphan*/  lseg; int /*<<< orphan*/  pnfs_error; } ;
struct bio {scalar_t__ bi_status; struct parallel_io* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bl_mark_devices_unavailable (struct nfs_pgio_header*,int) ; 
 int /*<<< orphan*/  pnfs_set_lo_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_parallel (struct parallel_io*) ; 

__attribute__((used)) static void bl_end_io_write(struct bio *bio)
{
	struct parallel_io *par = bio->bi_private;
	struct nfs_pgio_header *header = par->data;

	if (bio->bi_status) {
		if (!header->pnfs_error)
			header->pnfs_error = -EIO;
		pnfs_set_lo_fail(header->lseg);
		bl_mark_devices_unavailable(header, true);
	}
	bio_put(bio);
	put_parallel(par);
}