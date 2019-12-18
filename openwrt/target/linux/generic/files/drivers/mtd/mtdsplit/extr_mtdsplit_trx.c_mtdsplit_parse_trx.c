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
struct trx_header {scalar_t__ magic; size_t* offset; int /*<<< orphan*/  len; } ;
struct mtd_partition {size_t offset; size_t size; int /*<<< orphan*/  name; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {size_t size; int /*<<< orphan*/  name; scalar_t__ erasesize; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERNEL_PART_NAME ; 
 int /*<<< orphan*/  ROOTFS_PART_NAME ; 
 int /*<<< orphan*/  TRX_MAGIC ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtd_partition*) ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int read_trx_header (struct mtd_info*,size_t,struct trx_header*) ; 

__attribute__((used)) static int
mtdsplit_parse_trx(struct mtd_info *master,
		   const struct mtd_partition **pparts,
		   struct mtd_part_parser_data *data)
{
	struct mtd_partition *parts;
	struct trx_header hdr;
	int nr_parts;
	size_t offset;
	size_t trx_offset;
	size_t trx_size = 0;
	size_t rootfs_offset;
	size_t rootfs_size = 0;
	int ret;

	nr_parts = 2;
	parts = kzalloc(nr_parts * sizeof(*parts), GFP_KERNEL);
	if (!parts)
		return -ENOMEM;

	/* find trx image on erase block boundaries */
	for (offset = 0; offset < master->size; offset += master->erasesize) {
		trx_size = 0;

		ret = read_trx_header(master, offset, &hdr);
		if (ret)
			continue;

		if (hdr.magic != cpu_to_le32(TRX_MAGIC)) {
			pr_debug("no valid trx header found in \"%s\" at offset %llx\n",
				 master->name, (unsigned long long) offset);
			continue;
		}

		trx_size = le32_to_cpu(hdr.len);
		if ((offset + trx_size) > master->size) {
			pr_debug("trx image exceeds MTD device \"%s\"\n",
				 master->name);
			continue;
		}
		break;
	}

	if (trx_size == 0) {
		pr_debug("no trx header found in \"%s\"\n", master->name);
		ret = -ENODEV;
		goto err;
	}

	trx_offset = offset + hdr.offset[0];
	rootfs_offset = offset + hdr.offset[1];
	rootfs_size = master->size - rootfs_offset;
	trx_size = rootfs_offset - trx_offset;

	if (rootfs_size == 0) {
		pr_debug("no rootfs found in \"%s\"\n", master->name);
		ret = -ENODEV;
		goto err;
	}

	parts[0].name = KERNEL_PART_NAME;
	parts[0].offset = trx_offset;
	parts[0].size = trx_size;

	parts[1].name = ROOTFS_PART_NAME;
	parts[1].offset = rootfs_offset;
	parts[1].size = rootfs_size;

	*pparts = parts;
	return nr_parts;

err:
	kfree(parts);
	return ret;
}