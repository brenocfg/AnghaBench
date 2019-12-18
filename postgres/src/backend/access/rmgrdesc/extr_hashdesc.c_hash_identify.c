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
#define  XLOG_HASH_ADD_OVFL_PAGE 140 
#define  XLOG_HASH_DELETE 139 
#define  XLOG_HASH_INIT_BITMAP_PAGE 138 
#define  XLOG_HASH_INIT_META_PAGE 137 
#define  XLOG_HASH_INSERT 136 
#define  XLOG_HASH_MOVE_PAGE_CONTENTS 135 
#define  XLOG_HASH_SPLIT_ALLOCATE_PAGE 134 
#define  XLOG_HASH_SPLIT_CLEANUP 133 
#define  XLOG_HASH_SPLIT_COMPLETE 132 
#define  XLOG_HASH_SPLIT_PAGE 131 
#define  XLOG_HASH_SQUEEZE_PAGE 130 
#define  XLOG_HASH_UPDATE_META_PAGE 129 
#define  XLOG_HASH_VACUUM_ONE_PAGE 128 
 int XLR_INFO_MASK ; 

const char *
hash_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_HASH_INIT_META_PAGE:
			id = "INIT_META_PAGE";
			break;
		case XLOG_HASH_INIT_BITMAP_PAGE:
			id = "INIT_BITMAP_PAGE";
			break;
		case XLOG_HASH_INSERT:
			id = "INSERT";
			break;
		case XLOG_HASH_ADD_OVFL_PAGE:
			id = "ADD_OVFL_PAGE";
			break;
		case XLOG_HASH_SPLIT_ALLOCATE_PAGE:
			id = "SPLIT_ALLOCATE_PAGE";
			break;
		case XLOG_HASH_SPLIT_PAGE:
			id = "SPLIT_PAGE";
			break;
		case XLOG_HASH_SPLIT_COMPLETE:
			id = "SPLIT_COMPLETE";
			break;
		case XLOG_HASH_MOVE_PAGE_CONTENTS:
			id = "MOVE_PAGE_CONTENTS";
			break;
		case XLOG_HASH_SQUEEZE_PAGE:
			id = "SQUEEZE_PAGE";
			break;
		case XLOG_HASH_DELETE:
			id = "DELETE";
			break;
		case XLOG_HASH_SPLIT_CLEANUP:
			id = "SPLIT_CLEANUP";
			break;
		case XLOG_HASH_UPDATE_META_PAGE:
			id = "UPDATE_META_PAGE";
			break;
		case XLOG_HASH_VACUUM_ONE_PAGE:
			id = "VACUUM_ONE_PAGE";
	}

	return id;
}