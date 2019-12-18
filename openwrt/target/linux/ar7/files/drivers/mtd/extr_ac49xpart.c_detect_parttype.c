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
typedef  int /*<<< orphan*/  uint8_t ;
struct mtd_partition {int size; int /*<<< orphan*/  offset; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  magic ;

/* Variables and functions */
#define  AC49X_BOOTENV_MAGIC 134 
#define  AC49X_LINUX_MAGIC 133 
#define  AC49X_LOADER_MAGIC 132 
 int AC49X_PARTTYPE_BOOTENV ; 
 int AC49X_PARTTYPE_LINUX ; 
 int AC49X_PARTTYPE_LOADER ; 
 int AC49X_PARTTYPE_ROOTFS ; 
 int AC49X_PARTTYPE_UNKNOWN ; 
#define  CRAMFS_MAGIC 131 
#define  CRAMFS_MAGIC_WEND 130 
#define  JFFS2_SUPER_MAGIC 129 
#define  SQUASHFS_MAGIC 128 
 int /*<<< orphan*/  mtd_read (struct mtd_info*,int /*<<< orphan*/ ,int,size_t*,int /*<<< orphan*/ *) ; 

int detect_parttype(struct mtd_info *master, struct mtd_partition part)
{
	unsigned int magic;
	size_t len;

	if (part.size < 4)
		return -1;

	mtd_read(master, part.offset, sizeof(magic), &len,
		 (uint8_t *)&magic);

	if (len != sizeof(magic))
		return -1;

	switch (magic) {
	case AC49X_LOADER_MAGIC:
		return AC49X_PARTTYPE_LOADER;
	case AC49X_LINUX_MAGIC:
		return AC49X_PARTTYPE_LINUX;
	case SQUASHFS_MAGIC:
	case CRAMFS_MAGIC:
	case CRAMFS_MAGIC_WEND:
		return AC49X_PARTTYPE_ROOTFS;
	case AC49X_BOOTENV_MAGIC:
		return AC49X_PARTTYPE_BOOTENV;
	default:
		switch (magic & 0xFF) {
		case JFFS2_SUPER_MAGIC:
			return AC49X_PARTTYPE_ROOTFS;
		}
		switch (magic >> 8) {
		case JFFS2_SUPER_MAGIC:
			return AC49X_PARTTYPE_ROOTFS;
		}
		return AC49X_PARTTYPE_UNKNOWN;
	}
}