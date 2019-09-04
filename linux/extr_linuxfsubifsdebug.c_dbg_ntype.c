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
#define  UBIFS_CS_NODE 139 
#define  UBIFS_DATA_NODE 138 
#define  UBIFS_DENT_NODE 137 
#define  UBIFS_IDX_NODE 136 
#define  UBIFS_INO_NODE 135 
#define  UBIFS_MST_NODE 134 
#define  UBIFS_ORPH_NODE 133 
#define  UBIFS_PAD_NODE 132 
#define  UBIFS_REF_NODE 131 
#define  UBIFS_SB_NODE 130 
#define  UBIFS_TRUN_NODE 129 
#define  UBIFS_XENT_NODE 128 

const char *dbg_ntype(int type)
{
	switch (type) {
	case UBIFS_PAD_NODE:
		return "padding node";
	case UBIFS_SB_NODE:
		return "superblock node";
	case UBIFS_MST_NODE:
		return "master node";
	case UBIFS_REF_NODE:
		return "reference node";
	case UBIFS_INO_NODE:
		return "inode node";
	case UBIFS_DENT_NODE:
		return "direntry node";
	case UBIFS_XENT_NODE:
		return "xentry node";
	case UBIFS_DATA_NODE:
		return "data node";
	case UBIFS_TRUN_NODE:
		return "truncate node";
	case UBIFS_IDX_NODE:
		return "indexing node";
	case UBIFS_CS_NODE:
		return "commit start node";
	case UBIFS_ORPH_NODE:
		return "orphan node";
	default:
		return "unknown node";
	}
}