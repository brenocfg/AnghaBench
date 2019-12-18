#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int teSection ;
typedef  int teReqs ;
struct TYPE_11__ {int dumpId; int nDeps; scalar_t__ tag; scalar_t__ desc; int /*<<< orphan*/ * defn; int /*<<< orphan*/  hadDumper; scalar_t__ namespace; int /*<<< orphan*/ * dependencies; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_14__ {int /*<<< orphan*/ * head; } ;
struct TYPE_10__ {TYPE_3__* ropt; } ;
struct TYPE_13__ {TYPE_1__ public; } ;
struct TYPE_12__ {int dumpSections; scalar_t__ dataOnly; scalar_t__ binary_upgrade; scalar_t__ sequence_data; scalar_t__ schemaOnly; TYPE_5__ triggerNames; int /*<<< orphan*/  selTrigger; TYPE_5__ functionNames; int /*<<< orphan*/  selFunction; TYPE_5__ indexNames; int /*<<< orphan*/  selIndex; TYPE_5__ tableNames; int /*<<< orphan*/  selTable; scalar_t__ selTypes; TYPE_5__ schemaExcludeNames; TYPE_5__ schemaNames; scalar_t__ createDB; int /*<<< orphan*/ * idWanted; scalar_t__ no_subscriptions; scalar_t__ no_security_labels; scalar_t__ no_publications; scalar_t__ no_comments; scalar_t__ aclsSkip; } ;
typedef  TYPE_3__ RestoreOptions ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int DUMP_DATA ; 
 int DUMP_POST_DATA ; 
 int DUMP_PRE_DATA ; 
 int REQ_DATA ; 
 int REQ_SCHEMA ; 
 int REQ_SPECIAL ; 
#define  SECTION_DATA 130 
#define  SECTION_POST_DATA 129 
#define  SECTION_PRE_DATA 128 
 scalar_t__ TocIDRequired (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _tocEntryIsACL (TYPE_2__*) ; 
 scalar_t__ simple_string_list_member (TYPE_5__*,scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static teReqs
_tocEntryRequired(TocEntry *te, teSection curSection, ArchiveHandle *AH)
{
	teReqs		res = REQ_SCHEMA | REQ_DATA;
	RestoreOptions *ropt = AH->public.ropt;

	/* These items are treated specially */
	if (strcmp(te->desc, "ENCODING") == 0 ||
		strcmp(te->desc, "STDSTRINGS") == 0 ||
		strcmp(te->desc, "SEARCHPATH") == 0)
		return REQ_SPECIAL;

	/*
	 * DATABASE and DATABASE PROPERTIES also have a special rule: they are
	 * restored in createDB mode, and not restored otherwise, independently of
	 * all else.
	 */
	if (strcmp(te->desc, "DATABASE") == 0 ||
		strcmp(te->desc, "DATABASE PROPERTIES") == 0)
	{
		if (ropt->createDB)
			return REQ_SCHEMA;
		else
			return 0;
	}

	/*
	 * Process exclusions that affect certain classes of TOC entries.
	 */

	/* If it's an ACL, maybe ignore it */
	if (ropt->aclsSkip && _tocEntryIsACL(te))
		return 0;

	/* If it's a comment, maybe ignore it */
	if (ropt->no_comments && strcmp(te->desc, "COMMENT") == 0)
		return 0;

	/*
	 * If it's a publication or a table part of a publication, maybe ignore
	 * it.
	 */
	if (ropt->no_publications &&
		(strcmp(te->desc, "PUBLICATION") == 0 ||
		 strcmp(te->desc, "PUBLICATION TABLE") == 0))
		return 0;

	/* If it's a security label, maybe ignore it */
	if (ropt->no_security_labels && strcmp(te->desc, "SECURITY LABEL") == 0)
		return 0;

	/* If it's a subscription, maybe ignore it */
	if (ropt->no_subscriptions && strcmp(te->desc, "SUBSCRIPTION") == 0)
		return 0;

	/* Ignore it if section is not to be dumped/restored */
	switch (curSection)
	{
		case SECTION_PRE_DATA:
			if (!(ropt->dumpSections & DUMP_PRE_DATA))
				return 0;
			break;
		case SECTION_DATA:
			if (!(ropt->dumpSections & DUMP_DATA))
				return 0;
			break;
		case SECTION_POST_DATA:
			if (!(ropt->dumpSections & DUMP_POST_DATA))
				return 0;
			break;
		default:
			/* shouldn't get here, really, but ignore it */
			return 0;
	}

	/* Ignore it if rejected by idWanted[] (cf. SortTocFromFile) */
	if (ropt->idWanted && !ropt->idWanted[te->dumpId - 1])
		return 0;

	/*
	 * Check options for selective dump/restore.
	 */
	if (strcmp(te->desc, "ACL") == 0 ||
		strcmp(te->desc, "COMMENT") == 0 ||
		strcmp(te->desc, "SECURITY LABEL") == 0)
	{
		/* Database properties react to createDB, not selectivity options. */
		if (strncmp(te->tag, "DATABASE ", 9) == 0)
		{
			if (!ropt->createDB)
				return 0;
		}
		else if (ropt->schemaNames.head != NULL ||
				 ropt->schemaExcludeNames.head != NULL ||
				 ropt->selTypes)
		{
			/*
			 * In a selective dump/restore, we want to restore these dependent
			 * TOC entry types only if their parent object is being restored.
			 * Without selectivity options, we let through everything in the
			 * archive.  Note there may be such entries with no parent, eg
			 * non-default ACLs for built-in objects.
			 *
			 * This code depends on the parent having been marked already,
			 * which should be the case; if it isn't, perhaps due to
			 * SortTocFromFile rearrangement, skipping the dependent entry
			 * seems prudent anyway.
			 *
			 * Ideally we'd handle, eg, table CHECK constraints this way too.
			 * But it's hard to tell which of their dependencies is the one to
			 * consult.
			 */
			if (te->nDeps != 1 ||
				TocIDRequired(AH, te->dependencies[0]) == 0)
				return 0;
		}
	}
	else
	{
		/* Apply selective-restore rules for standalone TOC entries. */
		if (ropt->schemaNames.head != NULL)
		{
			/* If no namespace is specified, it means all. */
			if (!te->namespace)
				return 0;
			if (!simple_string_list_member(&ropt->schemaNames, te->namespace))
				return 0;
		}

		if (ropt->schemaExcludeNames.head != NULL &&
			te->namespace &&
			simple_string_list_member(&ropt->schemaExcludeNames, te->namespace))
			return 0;

		if (ropt->selTypes)
		{
			if (strcmp(te->desc, "TABLE") == 0 ||
				strcmp(te->desc, "TABLE DATA") == 0 ||
				strcmp(te->desc, "VIEW") == 0 ||
				strcmp(te->desc, "FOREIGN TABLE") == 0 ||
				strcmp(te->desc, "MATERIALIZED VIEW") == 0 ||
				strcmp(te->desc, "MATERIALIZED VIEW DATA") == 0 ||
				strcmp(te->desc, "SEQUENCE") == 0 ||
				strcmp(te->desc, "SEQUENCE SET") == 0)
			{
				if (!ropt->selTable)
					return 0;
				if (ropt->tableNames.head != NULL &&
					!simple_string_list_member(&ropt->tableNames, te->tag))
					return 0;
			}
			else if (strcmp(te->desc, "INDEX") == 0)
			{
				if (!ropt->selIndex)
					return 0;
				if (ropt->indexNames.head != NULL &&
					!simple_string_list_member(&ropt->indexNames, te->tag))
					return 0;
			}
			else if (strcmp(te->desc, "FUNCTION") == 0 ||
					 strcmp(te->desc, "AGGREGATE") == 0 ||
					 strcmp(te->desc, "PROCEDURE") == 0)
			{
				if (!ropt->selFunction)
					return 0;
				if (ropt->functionNames.head != NULL &&
					!simple_string_list_member(&ropt->functionNames, te->tag))
					return 0;
			}
			else if (strcmp(te->desc, "TRIGGER") == 0)
			{
				if (!ropt->selTrigger)
					return 0;
				if (ropt->triggerNames.head != NULL &&
					!simple_string_list_member(&ropt->triggerNames, te->tag))
					return 0;
			}
			else
				return 0;
		}
	}

	/*
	 * Determine whether the TOC entry contains schema and/or data components,
	 * and mask off inapplicable REQ bits.  If it had a dataDumper, assume
	 * it's both schema and data.  Otherwise it's probably schema-only, but
	 * there are exceptions.
	 */
	if (!te->hadDumper)
	{
		/*
		 * Special Case: If 'SEQUENCE SET' or anything to do with BLOBs, then
		 * it is considered a data entry.  We don't need to check for the
		 * BLOBS entry or old-style BLOB COMMENTS, because they will have
		 * hadDumper = true ... but we do need to check new-style BLOB ACLs,
		 * comments, etc.
		 */
		if (strcmp(te->desc, "SEQUENCE SET") == 0 ||
			strcmp(te->desc, "BLOB") == 0 ||
			(strcmp(te->desc, "ACL") == 0 &&
			 strncmp(te->tag, "LARGE OBJECT ", 13) == 0) ||
			(strcmp(te->desc, "COMMENT") == 0 &&
			 strncmp(te->tag, "LARGE OBJECT ", 13) == 0) ||
			(strcmp(te->desc, "SECURITY LABEL") == 0 &&
			 strncmp(te->tag, "LARGE OBJECT ", 13) == 0))
			res = res & REQ_DATA;
		else
			res = res & ~REQ_DATA;
	}

	/* If there's no definition command, there's no schema component */
	if (!te->defn || !te->defn[0])
		res = res & ~REQ_SCHEMA;

	/*
	 * Special case: <Init> type with <Max OID> tag; this is obsolete and we
	 * always ignore it.
	 */
	if ((strcmp(te->desc, "<Init>") == 0) && (strcmp(te->tag, "Max OID") == 0))
		return 0;

	/* Mask it if we only want schema */
	if (ropt->schemaOnly)
	{
		/*
		 * The sequence_data option overrides schemaOnly for SEQUENCE SET.
		 *
		 * In binary-upgrade mode, even with schemaOnly set, we do not mask
		 * out large objects.  (Only large object definitions, comments and
		 * other metadata should be generated in binary-upgrade mode, not the
		 * actual data, but that need not concern us here.)
		 */
		if (!(ropt->sequence_data && strcmp(te->desc, "SEQUENCE SET") == 0) &&
			!(ropt->binary_upgrade &&
			  (strcmp(te->desc, "BLOB") == 0 ||
			   (strcmp(te->desc, "ACL") == 0 &&
				strncmp(te->tag, "LARGE OBJECT ", 13) == 0) ||
			   (strcmp(te->desc, "COMMENT") == 0 &&
				strncmp(te->tag, "LARGE OBJECT ", 13) == 0) ||
			   (strcmp(te->desc, "SECURITY LABEL") == 0 &&
				strncmp(te->tag, "LARGE OBJECT ", 13) == 0))))
			res = res & REQ_SCHEMA;
	}

	/* Mask it if we only want data */
	if (ropt->dataOnly)
		res = res & REQ_DATA;

	return res;
}