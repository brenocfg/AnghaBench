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
struct TYPE_4__ {unsigned int max_write_same_len; int is_nonrot; scalar_t__ pi_prot_type; scalar_t__ hw_pi_prot_type; int /*<<< orphan*/  hw_queue_depth; int /*<<< orphan*/  hw_max_sectors; int /*<<< orphan*/  hw_block_size; } ;
struct se_device {TYPE_2__ dev_attrib; int /*<<< orphan*/  dev_flags; } ;
struct request_queue {int /*<<< orphan*/  nr_requests; } ;
struct bio_set {int /*<<< orphan*/  bio_integrity_pool; } ;
struct iblock_dev {int ibd_flags; struct bio_set ibd_bio_set; struct block_device* ibd_bd; int /*<<< orphan*/ * ibd_udev_path; int /*<<< orphan*/  ibd_readonly; } ;
struct block_device {int dummy; } ;
struct blk_integrity {TYPE_1__* profile; } ;
typedef  int fmode_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOSET_NEED_BVECS ; 
 int /*<<< orphan*/  DF_READ_ONLY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int IBDF_HAS_UDEV_PATH ; 
 int /*<<< orphan*/  IBLOCK_BIO_POOL_SIZE ; 
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int PTR_ERR (struct block_device*) ; 
 scalar_t__ TARGET_DIF_TYPE1_PROT ; 
 scalar_t__ TARGET_DIF_TYPE3_PROT ; 
 struct blk_integrity* bdev_get_integrity (struct block_device*) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdev_logical_block_size (struct block_device*) ; 
 unsigned int bdev_write_zeroes_sectors (struct block_device*) ; 
 int /*<<< orphan*/  bioset_exit (struct bio_set*) ; 
 int bioset_init (struct bio_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bioset_integrity_create (struct bio_set*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_nonrot (struct request_queue*) ; 
 struct block_device* blkdev_get_by_path (int /*<<< orphan*/ *,int,struct iblock_dev*) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  queue_max_hw_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ target_configure_unmap_from_queue (TYPE_2__*,struct request_queue*) ; 

__attribute__((used)) static int iblock_configure_device(struct se_device *dev)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);
	struct request_queue *q;
	struct block_device *bd = NULL;
	struct blk_integrity *bi;
	fmode_t mode;
	unsigned int max_write_zeroes_sectors;
	int ret = -ENOMEM;

	if (!(ib_dev->ibd_flags & IBDF_HAS_UDEV_PATH)) {
		pr_err("Missing udev_path= parameters for IBLOCK\n");
		return -EINVAL;
	}

	ret = bioset_init(&ib_dev->ibd_bio_set, IBLOCK_BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	if (ret) {
		pr_err("IBLOCK: Unable to create bioset\n");
		goto out;
	}

	pr_debug( "IBLOCK: Claiming struct block_device: %s\n",
			ib_dev->ibd_udev_path);

	mode = FMODE_READ|FMODE_EXCL;
	if (!ib_dev->ibd_readonly)
		mode |= FMODE_WRITE;
	else
		dev->dev_flags |= DF_READ_ONLY;

	bd = blkdev_get_by_path(ib_dev->ibd_udev_path, mode, ib_dev);
	if (IS_ERR(bd)) {
		ret = PTR_ERR(bd);
		goto out_free_bioset;
	}
	ib_dev->ibd_bd = bd;

	q = bdev_get_queue(bd);

	dev->dev_attrib.hw_block_size = bdev_logical_block_size(bd);
	dev->dev_attrib.hw_max_sectors = queue_max_hw_sectors(q);
	dev->dev_attrib.hw_queue_depth = q->nr_requests;

	if (target_configure_unmap_from_queue(&dev->dev_attrib, q))
		pr_debug("IBLOCK: BLOCK Discard support available,"
			 " disabled by default\n");

	/*
	 * Enable write same emulation for IBLOCK and use 0xFFFF as
	 * the smaller WRITE_SAME(10) only has a two-byte block count.
	 */
	max_write_zeroes_sectors = bdev_write_zeroes_sectors(bd);
	if (max_write_zeroes_sectors)
		dev->dev_attrib.max_write_same_len = max_write_zeroes_sectors;
	else
		dev->dev_attrib.max_write_same_len = 0xFFFF;

	if (blk_queue_nonrot(q))
		dev->dev_attrib.is_nonrot = 1;

	bi = bdev_get_integrity(bd);
	if (bi) {
		struct bio_set *bs = &ib_dev->ibd_bio_set;

		if (!strcmp(bi->profile->name, "T10-DIF-TYPE3-IP") ||
		    !strcmp(bi->profile->name, "T10-DIF-TYPE1-IP")) {
			pr_err("IBLOCK export of blk_integrity: %s not"
			       " supported\n", bi->profile->name);
			ret = -ENOSYS;
			goto out_blkdev_put;
		}

		if (!strcmp(bi->profile->name, "T10-DIF-TYPE3-CRC")) {
			dev->dev_attrib.pi_prot_type = TARGET_DIF_TYPE3_PROT;
		} else if (!strcmp(bi->profile->name, "T10-DIF-TYPE1-CRC")) {
			dev->dev_attrib.pi_prot_type = TARGET_DIF_TYPE1_PROT;
		}

		if (dev->dev_attrib.pi_prot_type) {
			if (bioset_integrity_create(bs, IBLOCK_BIO_POOL_SIZE) < 0) {
				pr_err("Unable to allocate bioset for PI\n");
				ret = -ENOMEM;
				goto out_blkdev_put;
			}
			pr_debug("IBLOCK setup BIP bs->bio_integrity_pool: %p\n",
				 &bs->bio_integrity_pool);
		}
		dev->dev_attrib.hw_pi_prot_type = dev->dev_attrib.pi_prot_type;
	}

	return 0;

out_blkdev_put:
	blkdev_put(ib_dev->ibd_bd, FMODE_WRITE|FMODE_READ|FMODE_EXCL);
out_free_bioset:
	bioset_exit(&ib_dev->ibd_bio_set);
out:
	return ret;
}