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
#define  XLOG_SPGIST_ADD_LEAF 135 
#define  XLOG_SPGIST_ADD_NODE 134 
#define  XLOG_SPGIST_MOVE_LEAFS 133 
#define  XLOG_SPGIST_PICKSPLIT 132 
#define  XLOG_SPGIST_SPLIT_TUPLE 131 
#define  XLOG_SPGIST_VACUUM_LEAF 130 
#define  XLOG_SPGIST_VACUUM_REDIRECT 129 
#define  XLOG_SPGIST_VACUUM_ROOT 128 
 int XLR_INFO_MASK ; 

const char *
spg_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_SPGIST_ADD_LEAF:
			id = "ADD_LEAF";
			break;
		case XLOG_SPGIST_MOVE_LEAFS:
			id = "MOVE_LEAFS";
			break;
		case XLOG_SPGIST_ADD_NODE:
			id = "ADD_NODE";
			break;
		case XLOG_SPGIST_SPLIT_TUPLE:
			id = "SPLIT_TUPLE";
			break;
		case XLOG_SPGIST_PICKSPLIT:
			id = "PICKSPLIT";
			break;
		case XLOG_SPGIST_VACUUM_LEAF:
			id = "VACUUM_LEAF";
			break;
		case XLOG_SPGIST_VACUUM_ROOT:
			id = "VACUUM_ROOT";
			break;
		case XLOG_SPGIST_VACUUM_REDIRECT:
			id = "VACUUM_REDIRECT";
			break;
	}

	return id;
}