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
typedef  int u32 ;
struct scsi_disk {int nr_zones; int zone_blocks; int zone_shift; TYPE_2__* device; int /*<<< orphan*/  capacity; TYPE_1__* disk; } ;
struct request_queue {int nr_zones; int /*<<< orphan*/  seq_zones_bitmap; int /*<<< orphan*/  seq_zones_wlock; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int use_16_for_rw; scalar_t__ use_10_for_rw; } ;
struct TYPE_3__ {struct request_queue* queue; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (unsigned long*) ; 
 int PTR_ERR (unsigned long*) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_chunk_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int /*<<< orphan*/  logical_to_sectors (TYPE_2__*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned long*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,size_t) ; 
 int round_up (int /*<<< orphan*/ ,int) ; 
 unsigned long* sd_zbc_alloc_zone_bitmap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_zbc_cleanup (struct scsi_disk*) ; 
 unsigned long* sd_zbc_setup_seq_zones_bitmap (struct scsi_disk*,int,int) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int sd_zbc_setup(struct scsi_disk *sdkp, u32 zone_blocks)
{
	struct request_queue *q = sdkp->disk->queue;
	u32 zone_shift = ilog2(zone_blocks);
	u32 nr_zones;
	int ret;

	/* chunk_sectors indicates the zone size */
	blk_queue_chunk_sectors(q,
			logical_to_sectors(sdkp->device, zone_blocks));
	nr_zones = round_up(sdkp->capacity, zone_blocks) >> zone_shift;

	/*
	 * Initialize the device request queue information if the number
	 * of zones changed.
	 */
	if (nr_zones != sdkp->nr_zones || nr_zones != q->nr_zones) {
		unsigned long *seq_zones_wlock = NULL, *seq_zones_bitmap = NULL;
		size_t zone_bitmap_size;

		if (nr_zones) {
			seq_zones_wlock = sd_zbc_alloc_zone_bitmap(nr_zones,
								   q->node);
			if (!seq_zones_wlock) {
				ret = -ENOMEM;
				goto err;
			}

			seq_zones_bitmap = sd_zbc_setup_seq_zones_bitmap(sdkp,
							zone_shift, nr_zones);
			if (IS_ERR(seq_zones_bitmap)) {
				ret = PTR_ERR(seq_zones_bitmap);
				kfree(seq_zones_wlock);
				goto err;
			}
		}
		zone_bitmap_size = BITS_TO_LONGS(nr_zones) *
			sizeof(unsigned long);
		blk_mq_freeze_queue(q);
		if (q->nr_zones != nr_zones) {
			/* READ16/WRITE16 is mandatory for ZBC disks */
			sdkp->device->use_16_for_rw = 1;
			sdkp->device->use_10_for_rw = 0;

			sdkp->zone_blocks = zone_blocks;
			sdkp->zone_shift = zone_shift;
			sdkp->nr_zones = nr_zones;
			q->nr_zones = nr_zones;
			swap(q->seq_zones_wlock, seq_zones_wlock);
			swap(q->seq_zones_bitmap, seq_zones_bitmap);
		} else if (memcmp(q->seq_zones_bitmap, seq_zones_bitmap,
				  zone_bitmap_size) != 0) {
			memcpy(q->seq_zones_bitmap, seq_zones_bitmap,
			       zone_bitmap_size);
		}
		blk_mq_unfreeze_queue(q);
		kfree(seq_zones_wlock);
		kfree(seq_zones_bitmap);
	}

	return 0;

err:
	sd_zbc_cleanup(sdkp);
	return ret;
}