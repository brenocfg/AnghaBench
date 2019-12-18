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
struct mtd_info_user {unsigned int writesize; unsigned int size; unsigned int length; scalar_t__ start; } ;
struct erase_info_user {unsigned int writesize; unsigned int size; unsigned int length; scalar_t__ start; } ;
struct bootcounter {void* magic; int count; void* checksum; } ;

/* Variables and functions */
 unsigned int BC_OFFSET_INCREMENT_MIN ; 
 void* BOOTCOUNT_MAGIC ; 
 int /*<<< orphan*/  DLOG_DEBUG (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DLOG_ERR (char*,...) ; 
 int /*<<< orphan*/  DLOG_NOTICE (char*,...) ; 
 int /*<<< orphan*/  DLOG_OPEN () ; 
 int /*<<< orphan*/  MEMERASE ; 
 int /*<<< orphan*/  MEMGETINFO ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mtd_info_user*) ; 
 int /*<<< orphan*/  memset (struct bootcounter*,int,unsigned int) ; 
 int mtd_check_open (char const*) ; 
 scalar_t__ page ; 
 int /*<<< orphan*/  pread (int,struct bootcounter*,int,unsigned int) ; 
 int pwrite (int,struct bootcounter*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sync () ; 

int mtd_resetbc(const char *mtd)
{
	struct mtd_info_user mtd_info;
	struct bootcounter *curr = (struct bootcounter *)page;
	unsigned int i;
	unsigned int bc_offset_increment;
	int last_count = 0;
	int num_bc;
	int fd;
	int ret;
	int retval = 0;

	DLOG_OPEN();

	fd = mtd_check_open(mtd);

	if (ioctl(fd, MEMGETINFO, &mtd_info) < 0) {
		DLOG_ERR("Unable to obtain mtd_info for given partition name.");

		retval = -1;
		goto out;
	}


	/* Detect need to override increment (for EA6350v3) */

	if (mtd_info.writesize < BC_OFFSET_INCREMENT_MIN) {

		bc_offset_increment = BC_OFFSET_INCREMENT_MIN;
		DLOG_DEBUG("Offset increment set to %i for writesize of %i",
			   bc_offset_increment, mtd_info.writesize);
	} else {

		bc_offset_increment = mtd_info.writesize;
	}

	num_bc = mtd_info.size / bc_offset_increment;

	for (i = 0; i < num_bc; i++) {
		pread(fd, curr, sizeof(*curr), i * bc_offset_increment);

		/* Existing code assumes erase is to 0xff; left as-is (2019) */

		if (curr->magic != BOOTCOUNT_MAGIC &&
		    curr->magic != 0xffffffff) {
			DLOG_ERR("Unexpected magic %08x at offset %08x; aborting.",
				 curr->magic, i * bc_offset_increment);

			retval = -2;
			goto out;
		}

		if (curr->magic == 0xffffffff)
			break;

		last_count = curr->count;
	}


	if (last_count == 0) {	/* bootcount is already 0 */

		retval = 0;
		goto out;
	}


	if (i == num_bc) {
		DLOG_NOTICE("Boot-count log full with %i entries; erasing (expected occasionally).",
			    i);

		struct erase_info_user erase_info;
		erase_info.start = 0;
		erase_info.length = mtd_info.size;

		ret = ioctl(fd, MEMERASE, &erase_info);
		if (ret < 0) {
			DLOG_ERR("Failed to erase boot-count log MTD; ioctl() MEMERASE returned %i",
				 ret);

			retval = -3;
			goto out;
		}

		i = 0;
	}

	memset(curr, 0xff, bc_offset_increment);

	curr->magic = BOOTCOUNT_MAGIC;
	curr->count = 0;
	curr->checksum = BOOTCOUNT_MAGIC;

	/* Assumes bc_offset_increment is a multiple of mtd_info.writesize */

	ret = pwrite(fd, curr, bc_offset_increment, i * bc_offset_increment);
	if (ret < 0) {
		DLOG_ERR("Failed to write boot-count log entry; pwrite() returned %i",
			 errno);
		retval = -4;
		goto out;

	} else {
		sync();

		DLOG_NOTICE("Boot count sucessfully reset to zero.");

		retval = 0;
		goto out;
	}

out:
	close(fd);
	return retval;
}