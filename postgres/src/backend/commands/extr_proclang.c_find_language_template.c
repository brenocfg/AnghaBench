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
struct TYPE_5__ {int /*<<< orphan*/  tmpldbacreate; int /*<<< orphan*/  tmpltrusted; } ;
struct TYPE_4__ {void* tmpllibrary; void* tmplhandler; void* tmplvalidator; void* tmplinline; int /*<<< orphan*/  tmpldbacreate; int /*<<< orphan*/  tmpltrusted; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ PLTemplate ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_pltemplate ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_pltemplate_tmplhandler ; 
 int /*<<< orphan*/  Anum_pg_pltemplate_tmplinline ; 
 int /*<<< orphan*/  Anum_pg_pltemplate_tmpllibrary ; 
 int /*<<< orphan*/  Anum_pg_pltemplate_tmplname ; 
 int /*<<< orphan*/  Anum_pg_pltemplate_tmplvalidator ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLTemplateNameIndexId ; 
 int /*<<< orphan*/  PLTemplateRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PLTemplate *
find_language_template(const char *languageName)
{
	PLTemplate *result;
	Relation	rel;
	SysScanDesc scan;
	ScanKeyData key;
	HeapTuple	tup;

	rel = table_open(PLTemplateRelationId, AccessShareLock);

	ScanKeyInit(&key,
				Anum_pg_pltemplate_tmplname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(languageName));
	scan = systable_beginscan(rel, PLTemplateNameIndexId, true,
							  NULL, 1, &key);

	tup = systable_getnext(scan);
	if (HeapTupleIsValid(tup))
	{
		Form_pg_pltemplate tmpl = (Form_pg_pltemplate) GETSTRUCT(tup);
		Datum		datum;
		bool		isnull;

		result = (PLTemplate *) palloc0(sizeof(PLTemplate));
		result->tmpltrusted = tmpl->tmpltrusted;
		result->tmpldbacreate = tmpl->tmpldbacreate;

		/* Remaining fields are variable-width so we need heap_getattr */
		datum = heap_getattr(tup, Anum_pg_pltemplate_tmplhandler,
							 RelationGetDescr(rel), &isnull);
		if (!isnull)
			result->tmplhandler = TextDatumGetCString(datum);

		datum = heap_getattr(tup, Anum_pg_pltemplate_tmplinline,
							 RelationGetDescr(rel), &isnull);
		if (!isnull)
			result->tmplinline = TextDatumGetCString(datum);

		datum = heap_getattr(tup, Anum_pg_pltemplate_tmplvalidator,
							 RelationGetDescr(rel), &isnull);
		if (!isnull)
			result->tmplvalidator = TextDatumGetCString(datum);

		datum = heap_getattr(tup, Anum_pg_pltemplate_tmpllibrary,
							 RelationGetDescr(rel), &isnull);
		if (!isnull)
			result->tmpllibrary = TextDatumGetCString(datum);

		/* Ignore template if handler or library info is missing */
		if (!result->tmplhandler || !result->tmpllibrary)
			result = NULL;
	}
	else
		result = NULL;

	systable_endscan(scan);

	table_close(rel, AccessShareLock);

	return result;
}