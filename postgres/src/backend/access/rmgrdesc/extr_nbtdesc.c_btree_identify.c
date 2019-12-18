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
typedef  int uint8 ;

/* Variables and functions */
#define  XLOG_BTREE_DELETE 140 
#define  XLOG_BTREE_INSERT_LEAF 139 
#define  XLOG_BTREE_INSERT_META 138 
#define  XLOG_BTREE_INSERT_UPPER 137 
#define  XLOG_BTREE_MARK_PAGE_HALFDEAD 136 
#define  XLOG_BTREE_META_CLEANUP 135 
#define  XLOG_BTREE_NEWROOT 134 
#define  XLOG_BTREE_REUSE_PAGE 133 
#define  XLOG_BTREE_SPLIT_L 132 
#define  XLOG_BTREE_SPLIT_R 131 
#define  XLOG_BTREE_UNLINK_PAGE 130 
#define  XLOG_BTREE_UNLINK_PAGE_META 129 
#define  XLOG_BTREE_VACUUM 128 
 int XLR_INFO_MASK ; 

const char *
btree_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_BTREE_INSERT_LEAF:
			id = "INSERT_LEAF";
			break;
		case XLOG_BTREE_INSERT_UPPER:
			id = "INSERT_UPPER";
			break;
		case XLOG_BTREE_INSERT_META:
			id = "INSERT_META";
			break;
		case XLOG_BTREE_SPLIT_L:
			id = "SPLIT_L";
			break;
		case XLOG_BTREE_SPLIT_R:
			id = "SPLIT_R";
			break;
		case XLOG_BTREE_VACUUM:
			id = "VACUUM";
			break;
		case XLOG_BTREE_DELETE:
			id = "DELETE";
			break;
		case XLOG_BTREE_MARK_PAGE_HALFDEAD:
			id = "MARK_PAGE_HALFDEAD";
			break;
		case XLOG_BTREE_UNLINK_PAGE:
			id = "UNLINK_PAGE";
			break;
		case XLOG_BTREE_UNLINK_PAGE_META:
			id = "UNLINK_PAGE_META";
			break;
		case XLOG_BTREE_NEWROOT:
			id = "NEWROOT";
			break;
		case XLOG_BTREE_REUSE_PAGE:
			id = "REUSE_PAGE";
			break;
		case XLOG_BTREE_META_CLEANUP:
			id = "META_CLEANUP";
			break;
	}

	return id;
}