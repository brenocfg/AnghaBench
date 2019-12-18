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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int DT_BLK ; 
 unsigned int DT_CHR ; 
 unsigned int DT_DIR ; 
 unsigned int DT_FIFO ; 
 unsigned int DT_LNK ; 
 unsigned int DT_REG ; 
 unsigned int DT_SOCK ; 
#define  UBIFS_ITYPE_BLK 134 
#define  UBIFS_ITYPE_CHR 133 
#define  UBIFS_ITYPE_DIR 132 
#define  UBIFS_ITYPE_FIFO 131 
#define  UBIFS_ITYPE_LNK 130 
#define  UBIFS_ITYPE_REG 129 
#define  UBIFS_ITYPE_SOCK 128 

__attribute__((used)) static unsigned int vfs_dent_type(uint8_t type)
{
	switch (type) {
	case UBIFS_ITYPE_REG:
		return DT_REG;
	case UBIFS_ITYPE_DIR:
		return DT_DIR;
	case UBIFS_ITYPE_LNK:
		return DT_LNK;
	case UBIFS_ITYPE_BLK:
		return DT_BLK;
	case UBIFS_ITYPE_CHR:
		return DT_CHR;
	case UBIFS_ITYPE_FIFO:
		return DT_FIFO;
	case UBIFS_ITYPE_SOCK:
		return DT_SOCK;
	default:
		BUG();
	}
	return 0;
}