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
#define  XLOG_GIN_CREATE_PTREE 136 
#define  XLOG_GIN_DELETE_LISTPAGE 135 
#define  XLOG_GIN_DELETE_PAGE 134 
#define  XLOG_GIN_INSERT 133 
#define  XLOG_GIN_INSERT_LISTPAGE 132 
#define  XLOG_GIN_SPLIT 131 
#define  XLOG_GIN_UPDATE_META_PAGE 130 
#define  XLOG_GIN_VACUUM_DATA_LEAF_PAGE 129 
#define  XLOG_GIN_VACUUM_PAGE 128 
 int XLR_INFO_MASK ; 

const char *
gin_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_GIN_CREATE_PTREE:
			id = "CREATE_PTREE";
			break;
		case XLOG_GIN_INSERT:
			id = "INSERT";
			break;
		case XLOG_GIN_SPLIT:
			id = "SPLIT";
			break;
		case XLOG_GIN_VACUUM_PAGE:
			id = "VACUUM_PAGE";
			break;
		case XLOG_GIN_VACUUM_DATA_LEAF_PAGE:
			id = "VACUUM_DATA_LEAF_PAGE";
			break;
		case XLOG_GIN_DELETE_PAGE:
			id = "DELETE_PAGE";
			break;
		case XLOG_GIN_UPDATE_META_PAGE:
			id = "UPDATE_META_PAGE";
			break;
		case XLOG_GIN_INSERT_LISTPAGE:
			id = "INSERT_LISTPAGE";
			break;
		case XLOG_GIN_DELETE_LISTPAGE:
			id = "DELETE_LISTPAGE";
			break;
	}

	return id;
}