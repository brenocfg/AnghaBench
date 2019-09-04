#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_8__ {int altmap_valid; struct resource res; int /*<<< orphan*/  kill; int /*<<< orphan*/ * ref; } ;
struct request_queue {int size; int pfn_flags; int data_offset; int pfn_pad; int /*<<< orphan*/  bb_state; struct dax_device* dax_dev; int /*<<< orphan*/  bb; TYPE_2__* backing_dev_info; struct gendisk* disk; struct request_queue* queuedata; void* virt_addr; int /*<<< orphan*/  phys_addr; TYPE_3__ pgmap; int /*<<< orphan*/  q_usage_counter; } ;
struct pmem_device {int size; int pfn_flags; int data_offset; int pfn_pad; int /*<<< orphan*/  bb_state; struct dax_device* dax_dev; int /*<<< orphan*/  bb; TYPE_2__* backing_dev_info; struct gendisk* disk; struct pmem_device* queuedata; void* virt_addr; int /*<<< orphan*/  phys_addr; TYPE_3__ pgmap; int /*<<< orphan*/  q_usage_counter; } ;
struct nd_region {int dummy; } ;
struct nd_pfn_sb {int /*<<< orphan*/  dataoff; } ;
struct nd_pfn {struct nd_pfn_sb* pfn_sb; } ;
struct nd_namespace_io {struct resource res; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct gendisk {int /*<<< orphan*/  disk_name; int /*<<< orphan*/ * bb; struct request_queue* queue; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fops; } ;
struct TYPE_6__ {int /*<<< orphan*/  sd; } ;
struct device {TYPE_1__ kobj; int /*<<< orphan*/  groups; int /*<<< orphan*/  parent; } ;
struct dax_device {int dummy; } ;
typedef  int /*<<< orphan*/  bb_res ;
struct TYPE_7__ {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_MEMREMAP_PMEM ; 
 int /*<<< orphan*/  BDI_CAP_SYNCHRONOUS_IO ; 
 int /*<<< orphan*/  CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PFN_DEV ; 
 int PFN_MAP ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  QUEUE_FLAG_DAX ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct dax_device* alloc_dax (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gendisk* alloc_disk_node (int /*<<< orphan*/ ,int) ; 
 struct request_queue* blk_alloc_queue_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_make_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_write_cache (struct request_queue*,int,int) ; 
 int /*<<< orphan*/  dax_write_cache (struct dax_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct request_queue*) ; 
 int dev_to_node (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_add_disk (struct device*,struct gendisk*) ; 
 scalar_t__ devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ devm_init_badblocks (struct device*,int /*<<< orphan*/ *) ; 
 struct request_queue* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_memremap (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* devm_memremap_pages (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  devm_nsio_disable (struct device*,struct nd_namespace_io*) ; 
 int /*<<< orphan*/  devm_request_mem_region (struct device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct device* disk_to_dev (struct gendisk*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct resource*,struct resource*,int) ; 
 int /*<<< orphan*/  nvdimm_badblocks_populate (struct nd_region*,int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  nvdimm_has_cache (struct nd_region*) ; 
 int nvdimm_has_flush (struct nd_region*) ; 
 int /*<<< orphan*/  nvdimm_namespace_disk_name (struct nd_namespace_common*,int /*<<< orphan*/ ) ; 
 int nvdimm_setup_pfn (struct nd_pfn*,TYPE_3__*) ; 
 int /*<<< orphan*/  pmem_attribute_groups ; 
 int /*<<< orphan*/  pmem_dax_ops ; 
 int /*<<< orphan*/  pmem_fops ; 
 int /*<<< orphan*/  pmem_freeze_queue ; 
 int /*<<< orphan*/  pmem_make_request ; 
 int /*<<< orphan*/  pmem_release_disk ; 
 int /*<<< orphan*/  pmem_release_queue ; 
 int /*<<< orphan*/  pmem_sector_size (struct nd_namespace_common*) ; 
 scalar_t__ pmem_should_map_pages (struct device*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 void* resource_size (struct resource*) ; 
 int /*<<< orphan*/  revalidate_disk (struct gendisk*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 scalar_t__ setup_pagemap_fsdax (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_get_dirent (int /*<<< orphan*/ ,char*) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmem_attach_disk(struct device *dev,
		struct nd_namespace_common *ndns)
{
	struct nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	struct nd_region *nd_region = to_nd_region(dev->parent);
	int nid = dev_to_node(dev), fua;
	struct resource *res = &nsio->res;
	struct resource bb_res;
	struct nd_pfn *nd_pfn = NULL;
	struct dax_device *dax_dev;
	struct nd_pfn_sb *pfn_sb;
	struct pmem_device *pmem;
	struct request_queue *q;
	struct device *gendev;
	struct gendisk *disk;
	void *addr;
	int rc;

	pmem = devm_kzalloc(dev, sizeof(*pmem), GFP_KERNEL);
	if (!pmem)
		return -ENOMEM;

	/* while nsio_rw_bytes is active, parse a pfn info block if present */
	if (is_nd_pfn(dev)) {
		nd_pfn = to_nd_pfn(dev);
		rc = nvdimm_setup_pfn(nd_pfn, &pmem->pgmap);
		if (rc)
			return rc;
	}

	/* we're attaching a block device, disable raw namespace access */
	devm_nsio_disable(dev, nsio);

	dev_set_drvdata(dev, pmem);
	pmem->phys_addr = res->start;
	pmem->size = resource_size(res);
	fua = nvdimm_has_flush(nd_region);
	if (!IS_ENABLED(CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE) || fua < 0) {
		dev_warn(dev, "unable to guarantee persistence of writes\n");
		fua = 0;
	}

	if (!devm_request_mem_region(dev, res->start, resource_size(res),
				dev_name(&ndns->dev))) {
		dev_warn(dev, "could not reserve region %pR\n", res);
		return -EBUSY;
	}

	q = blk_alloc_queue_node(GFP_KERNEL, dev_to_node(dev), NULL);
	if (!q)
		return -ENOMEM;

	if (devm_add_action_or_reset(dev, pmem_release_queue, q))
		return -ENOMEM;

	pmem->pfn_flags = PFN_DEV;
	pmem->pgmap.ref = &q->q_usage_counter;
	pmem->pgmap.kill = pmem_freeze_queue;
	if (is_nd_pfn(dev)) {
		if (setup_pagemap_fsdax(dev, &pmem->pgmap))
			return -ENOMEM;
		addr = devm_memremap_pages(dev, &pmem->pgmap);
		pfn_sb = nd_pfn->pfn_sb;
		pmem->data_offset = le64_to_cpu(pfn_sb->dataoff);
		pmem->pfn_pad = resource_size(res) -
			resource_size(&pmem->pgmap.res);
		pmem->pfn_flags |= PFN_MAP;
		memcpy(&bb_res, &pmem->pgmap.res, sizeof(bb_res));
		bb_res.start += pmem->data_offset;
	} else if (pmem_should_map_pages(dev)) {
		memcpy(&pmem->pgmap.res, &nsio->res, sizeof(pmem->pgmap.res));
		pmem->pgmap.altmap_valid = false;
		if (setup_pagemap_fsdax(dev, &pmem->pgmap))
			return -ENOMEM;
		addr = devm_memremap_pages(dev, &pmem->pgmap);
		pmem->pfn_flags |= PFN_MAP;
		memcpy(&bb_res, &pmem->pgmap.res, sizeof(bb_res));
	} else {
		addr = devm_memremap(dev, pmem->phys_addr,
				pmem->size, ARCH_MEMREMAP_PMEM);
		memcpy(&bb_res, &nsio->res, sizeof(bb_res));
	}

	if (IS_ERR(addr))
		return PTR_ERR(addr);
	pmem->virt_addr = addr;

	blk_queue_write_cache(q, true, fua);
	blk_queue_make_request(q, pmem_make_request);
	blk_queue_physical_block_size(q, PAGE_SIZE);
	blk_queue_logical_block_size(q, pmem_sector_size(ndns));
	blk_queue_max_hw_sectors(q, UINT_MAX);
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	if (pmem->pfn_flags & PFN_MAP)
		blk_queue_flag_set(QUEUE_FLAG_DAX, q);
	q->queuedata = pmem;

	disk = alloc_disk_node(0, nid);
	if (!disk)
		return -ENOMEM;
	pmem->disk = disk;

	disk->fops		= &pmem_fops;
	disk->queue		= q;
	disk->flags		= GENHD_FL_EXT_DEVT;
	disk->queue->backing_dev_info->capabilities |= BDI_CAP_SYNCHRONOUS_IO;
	nvdimm_namespace_disk_name(ndns, disk->disk_name);
	set_capacity(disk, (pmem->size - pmem->pfn_pad - pmem->data_offset)
			/ 512);
	if (devm_init_badblocks(dev, &pmem->bb))
		return -ENOMEM;
	nvdimm_badblocks_populate(nd_region, &pmem->bb, &bb_res);
	disk->bb = &pmem->bb;

	dax_dev = alloc_dax(pmem, disk->disk_name, &pmem_dax_ops);
	if (!dax_dev) {
		put_disk(disk);
		return -ENOMEM;
	}
	dax_write_cache(dax_dev, nvdimm_has_cache(nd_region));
	pmem->dax_dev = dax_dev;

	gendev = disk_to_dev(disk);
	gendev->groups = pmem_attribute_groups;

	device_add_disk(dev, disk);
	if (devm_add_action_or_reset(dev, pmem_release_disk, pmem))
		return -ENOMEM;

	revalidate_disk(disk);

	pmem->bb_state = sysfs_get_dirent(disk_to_dev(disk)->kobj.sd,
					  "badblocks");
	if (!pmem->bb_state)
		dev_warn(dev, "'badblocks' notification disabled\n");

	return 0;
}