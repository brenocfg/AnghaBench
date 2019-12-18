#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int numatts; char const** attnames; TYPE_1__ dobj; } ;
typedef  TYPE_2__ TableInfo ;

/* Variables and functions */
#define  MaxCommandIdAttributeNumber 133 
#define  MaxTransactionIdAttributeNumber 132 
#define  MinCommandIdAttributeNumber 131 
#define  MinTransactionIdAttributeNumber 130 
#define  SelfItemPointerAttributeNumber 129 
#define  TableOidAttributeNumber 128 
 int /*<<< orphan*/  fatal (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
getAttrName(int attrnum, TableInfo *tblInfo)
{
	if (attrnum > 0 && attrnum <= tblInfo->numatts)
		return tblInfo->attnames[attrnum - 1];
	switch (attrnum)
	{
		case SelfItemPointerAttributeNumber:
			return "ctid";
		case MinTransactionIdAttributeNumber:
			return "xmin";
		case MinCommandIdAttributeNumber:
			return "cmin";
		case MaxTransactionIdAttributeNumber:
			return "xmax";
		case MaxCommandIdAttributeNumber:
			return "cmax";
		case TableOidAttributeNumber:
			return "tableoid";
	}
	fatal("invalid column number %d for table \"%s\"",
		  attrnum, tblInfo->dobj.name);
	return NULL;				/* keep compiler quiet */
}