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

/* Variables and functions */
#define  UBIFS_ITYPE_BLK 134 
#define  UBIFS_ITYPE_CHR 133 
#define  UBIFS_ITYPE_DIR 132 
#define  UBIFS_ITYPE_FIFO 131 
#define  UBIFS_ITYPE_LNK 130 
#define  UBIFS_ITYPE_REG 129 
#define  UBIFS_ITYPE_SOCK 128 

__attribute__((used)) static const char *get_dent_type(int type)
{
	switch (type) {
	case UBIFS_ITYPE_REG:
		return "file";
	case UBIFS_ITYPE_DIR:
		return "dir";
	case UBIFS_ITYPE_LNK:
		return "symlink";
	case UBIFS_ITYPE_BLK:
		return "blkdev";
	case UBIFS_ITYPE_CHR:
		return "char dev";
	case UBIFS_ITYPE_FIFO:
		return "fifo";
	case UBIFS_ITYPE_SOCK:
		return "socket";
	default:
		return "unknown/invalid type";
	}
}