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
typedef  scalar_t__ uint32_t ;
struct uboot_args {scalar_t__ magic; } ;
struct erase_info_user {int /*<<< orphan*/  length; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMERASE ; 
 scalar_t__ TPL_NO_RECOVER_MAGIC ; 
 scalar_t__ TPL_RECOVER_MAGIC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  erasesize ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct uboot_args*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct erase_info_user*) ; 
 struct uboot_args* malloc (int /*<<< orphan*/ ) ; 
 int mtd_check_open (char const*) ; 
 int /*<<< orphan*/  pread (int,struct uboot_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pwrite (int,struct uboot_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sync () ; 

int mtd_tpl_recoverflag_write(const char *mtd, const bool recovery_active)
{
	struct erase_info_user erase_info;
	struct uboot_args *args;
	uint32_t magic;
	int ret = 0;
	int fd;

	args = malloc(erasesize);
	if (!args) {
		fprintf(stderr, "Could not allocate memory!\n");
		return -1;
	}

	fd = mtd_check_open(mtd);
	if (fd < 0) {
		fprintf(stderr, "Could not open mtd device: %s\n", mtd);
		ret = -1;
		goto out;
	}

	/* read first block (containing the magic) */
	pread(fd, args, erasesize, 0);

	/* set magic to desired value */
	magic = TPL_RECOVER_MAGIC;
	if (!recovery_active)
		magic = TPL_NO_RECOVER_MAGIC;

	/* no need to write when magic is already set correctly */
	if (magic == args->magic)
		goto out;

	/* erase first block (containing the magic) */
	erase_info.start = 0;
	erase_info.length = erasesize;

	ret = ioctl(fd, MEMERASE, &erase_info);
	if (ret < 0) {
		fprintf(stderr, "failed to erase block: %i\n", ret);
		goto out;
	}

	/* write magic to flash */
	args->magic = magic;

	ret = pwrite(fd, args, erasesize, 0);
	if (ret < 0)
		fprintf(stderr, "failed to write: %i\n", ret);

	sync();
out:
	free(args);
	close(fd);

	return ret;
}