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
#define  XLOG_GIST_DELETE 132 
#define  XLOG_GIST_PAGE_DELETE 131 
#define  XLOG_GIST_PAGE_REUSE 130 
#define  XLOG_GIST_PAGE_SPLIT 129 
#define  XLOG_GIST_PAGE_UPDATE 128 
 int XLR_INFO_MASK ; 

const char *
gist_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_GIST_PAGE_UPDATE:
			id = "PAGE_UPDATE";
			break;
		case XLOG_GIST_DELETE:
			id = "DELETE";
			break;
		case XLOG_GIST_PAGE_REUSE:
			id = "PAGE_REUSE";
			break;
		case XLOG_GIST_PAGE_SPLIT:
			id = "PAGE_SPLIT";
			break;
		case XLOG_GIST_PAGE_DELETE:
			id = "PAGE_DELETE";
			break;
	}

	return id;
}