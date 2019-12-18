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
typedef  int Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  ConversionRelationId 133 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OidIsValid (int) ; 
#define  StatisticExtRelationId 132 
#define  TSConfigRelationId 131 
#define  TSDictionaryRelationId 130 
#define  TSParserRelationId 129 
#define  TSTemplateRelationId 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (int) ; 
 char* gettext_noop (char*) ; 

__attribute__((used)) static void
report_namespace_conflict(Oid classId, const char *name, Oid nspOid)
{
	char	   *msgfmt;

	Assert(OidIsValid(nspOid));

	switch (classId)
	{
		case ConversionRelationId:
			Assert(OidIsValid(nspOid));
			msgfmt = gettext_noop("conversion \"%s\" already exists in schema \"%s\"");
			break;
		case StatisticExtRelationId:
			Assert(OidIsValid(nspOid));
			msgfmt = gettext_noop("statistics object \"%s\" already exists in schema \"%s\"");
			break;
		case TSParserRelationId:
			Assert(OidIsValid(nspOid));
			msgfmt = gettext_noop("text search parser \"%s\" already exists in schema \"%s\"");
			break;
		case TSDictionaryRelationId:
			Assert(OidIsValid(nspOid));
			msgfmt = gettext_noop("text search dictionary \"%s\" already exists in schema \"%s\"");
			break;
		case TSTemplateRelationId:
			Assert(OidIsValid(nspOid));
			msgfmt = gettext_noop("text search template \"%s\" already exists in schema \"%s\"");
			break;
		case TSConfigRelationId:
			Assert(OidIsValid(nspOid));
			msgfmt = gettext_noop("text search configuration \"%s\" already exists in schema \"%s\"");
			break;
		default:
			elog(ERROR, "unsupported object class %u", classId);
			break;
	}

	ereport(ERROR,
			(errcode(ERRCODE_DUPLICATE_OBJECT),
			 errmsg(msgfmt, name, get_namespace_name(nspOid))));
}