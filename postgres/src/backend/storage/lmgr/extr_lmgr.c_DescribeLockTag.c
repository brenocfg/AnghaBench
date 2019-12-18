#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int locktag_field1; scalar_t__ locktag_type; int /*<<< orphan*/  locktag_field4; int /*<<< orphan*/  locktag_field3; int /*<<< orphan*/  locktag_field2; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  LockTagType ;
typedef  TYPE_1__ LOCKTAG ;

/* Variables and functions */
#define  LOCKTAG_ADVISORY 137 
#define  LOCKTAG_OBJECT 136 
#define  LOCKTAG_PAGE 135 
#define  LOCKTAG_RELATION 134 
#define  LOCKTAG_RELATION_EXTEND 133 
#define  LOCKTAG_SPECULATIVE_TOKEN 132 
#define  LOCKTAG_TRANSACTION 131 
#define  LOCKTAG_TUPLE 130 
#define  LOCKTAG_USERLOCK 129 
#define  LOCKTAG_VIRTUALTRANSACTION 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 

void
DescribeLockTag(StringInfo buf, const LOCKTAG *tag)
{
	switch ((LockTagType) tag->locktag_type)
	{
		case LOCKTAG_RELATION:
			appendStringInfo(buf,
							 _("relation %u of database %u"),
							 tag->locktag_field2,
							 tag->locktag_field1);
			break;
		case LOCKTAG_RELATION_EXTEND:
			appendStringInfo(buf,
							 _("extension of relation %u of database %u"),
							 tag->locktag_field2,
							 tag->locktag_field1);
			break;
		case LOCKTAG_PAGE:
			appendStringInfo(buf,
							 _("page %u of relation %u of database %u"),
							 tag->locktag_field3,
							 tag->locktag_field2,
							 tag->locktag_field1);
			break;
		case LOCKTAG_TUPLE:
			appendStringInfo(buf,
							 _("tuple (%u,%u) of relation %u of database %u"),
							 tag->locktag_field3,
							 tag->locktag_field4,
							 tag->locktag_field2,
							 tag->locktag_field1);
			break;
		case LOCKTAG_TRANSACTION:
			appendStringInfo(buf,
							 _("transaction %u"),
							 tag->locktag_field1);
			break;
		case LOCKTAG_VIRTUALTRANSACTION:
			appendStringInfo(buf,
							 _("virtual transaction %d/%u"),
							 tag->locktag_field1,
							 tag->locktag_field2);
			break;
		case LOCKTAG_SPECULATIVE_TOKEN:
			appendStringInfo(buf,
							 _("speculative token %u of transaction %u"),
							 tag->locktag_field2,
							 tag->locktag_field1);
			break;
		case LOCKTAG_OBJECT:
			appendStringInfo(buf,
							 _("object %u of class %u of database %u"),
							 tag->locktag_field3,
							 tag->locktag_field2,
							 tag->locktag_field1);
			break;
		case LOCKTAG_USERLOCK:
			/* reserved for old contrib code, now on pgfoundry */
			appendStringInfo(buf,
							 _("user lock [%u,%u,%u]"),
							 tag->locktag_field1,
							 tag->locktag_field2,
							 tag->locktag_field3);
			break;
		case LOCKTAG_ADVISORY:
			appendStringInfo(buf,
							 _("advisory lock [%u,%u,%u,%u]"),
							 tag->locktag_field1,
							 tag->locktag_field2,
							 tag->locktag_field3,
							 tag->locktag_field4);
			break;
		default:
			appendStringInfo(buf,
							 _("unrecognized locktag type %d"),
							 (int) tag->locktag_type);
			break;
	}
}