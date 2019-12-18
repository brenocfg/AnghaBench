#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeInfo ;
typedef  int /*<<< orphan*/  TableInfo ;
struct TYPE_42__ {int /*<<< orphan*/  dopt; } ;
typedef  int /*<<< orphan*/  OprInfo ;
typedef  int /*<<< orphan*/  NamespaceInfo ;
typedef  int /*<<< orphan*/  InhInfo ;
typedef  int /*<<< orphan*/  FuncInfo ;
typedef  int /*<<< orphan*/  ExtensionInfo ;
typedef  int /*<<< orphan*/  CollInfo ;
typedef  TYPE_1__ Archive ;

/* Variables and functions */
 void* buildIndexArray (int /*<<< orphan*/ *,int,int) ; 
 void* collinfoindex ; 
 void* extinfoindex ; 
 int /*<<< orphan*/  flagInhAttrs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flagInhIndexes (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flagInhTables (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 void* funinfoindex ; 
 int /*<<< orphan*/  getAccessMethods (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getAggregates (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getCasts (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * getCollations (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getConstraints (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getConversions (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getDefaultACLs (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getEventTriggers (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getExtendedStatistics (TYPE_1__*) ; 
 int /*<<< orphan*/  getExtensionMembership (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * getExtensions (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getForeignDataWrappers (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getForeignServers (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * getFuncs (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getIndexes (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * getInherits (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * getNamespaces (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getOpclasses (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * getOperators (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getOpfamilies (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getOwnedSeqs (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getPolicies (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getProcLangs (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getPublicationTables (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  getPublications (TYPE_1__*) ; 
 int /*<<< orphan*/  getRules (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getSubscriptions (TYPE_1__*) ; 
 int /*<<< orphan*/  getTSConfigurations (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getTSDictionaries (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getTSParsers (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getTSTemplates (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getTableAttrs (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * getTables (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getTransforms (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  getTriggers (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * getTypes (TYPE_1__*,int*) ; 
 void* nspinfoindex ; 
 int numCollations ; 
 int numExtensions ; 
 int numFuncs ; 
 int numNamespaces ; 
 int numOperators ; 
 int numTables ; 
 int numTypes ; 
 void* oprinfoindex ; 
 int /*<<< orphan*/  pg_log_info (char*) ; 
 int /*<<< orphan*/  processExtensionTables (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 void* tblinfoindex ; 
 void* typinfoindex ; 

TableInfo *
getSchemaData(Archive *fout, int *numTablesPtr)
{
	TableInfo  *tblinfo;
	TypeInfo   *typinfo;
	FuncInfo   *funinfo;
	OprInfo    *oprinfo;
	CollInfo   *collinfo;
	NamespaceInfo *nspinfo;
	ExtensionInfo *extinfo;
	InhInfo    *inhinfo;
	int			numAggregates;
	int			numInherits;
	int			numRules;
	int			numProcLangs;
	int			numCasts;
	int			numTransforms;
	int			numAccessMethods;
	int			numOpclasses;
	int			numOpfamilies;
	int			numConversions;
	int			numTSParsers;
	int			numTSTemplates;
	int			numTSDicts;
	int			numTSConfigs;
	int			numForeignDataWrappers;
	int			numForeignServers;
	int			numDefaultACLs;
	int			numEventTriggers;

	/*
	 * We must read extensions and extension membership info first, because
	 * extension membership needs to be consultable during decisions about
	 * whether other objects are to be dumped.
	 */
	pg_log_info("reading extensions");
	extinfo = getExtensions(fout, &numExtensions);
	extinfoindex = buildIndexArray(extinfo, numExtensions, sizeof(ExtensionInfo));

	pg_log_info("identifying extension members");
	getExtensionMembership(fout, extinfo, numExtensions);

	pg_log_info("reading schemas");
	nspinfo = getNamespaces(fout, &numNamespaces);
	nspinfoindex = buildIndexArray(nspinfo, numNamespaces, sizeof(NamespaceInfo));

	/*
	 * getTables should be done as soon as possible, so as to minimize the
	 * window between starting our transaction and acquiring per-table locks.
	 * However, we have to do getNamespaces first because the tables get
	 * linked to their containing namespaces during getTables.
	 */
	pg_log_info("reading user-defined tables");
	tblinfo = getTables(fout, &numTables);
	tblinfoindex = buildIndexArray(tblinfo, numTables, sizeof(TableInfo));

	/* Do this after we've built tblinfoindex */
	getOwnedSeqs(fout, tblinfo, numTables);

	pg_log_info("reading user-defined functions");
	funinfo = getFuncs(fout, &numFuncs);
	funinfoindex = buildIndexArray(funinfo, numFuncs, sizeof(FuncInfo));

	/* this must be after getTables and getFuncs */
	pg_log_info("reading user-defined types");
	typinfo = getTypes(fout, &numTypes);
	typinfoindex = buildIndexArray(typinfo, numTypes, sizeof(TypeInfo));

	/* this must be after getFuncs, too */
	pg_log_info("reading procedural languages");
	getProcLangs(fout, &numProcLangs);

	pg_log_info("reading user-defined aggregate functions");
	getAggregates(fout, &numAggregates);

	pg_log_info("reading user-defined operators");
	oprinfo = getOperators(fout, &numOperators);
	oprinfoindex = buildIndexArray(oprinfo, numOperators, sizeof(OprInfo));

	pg_log_info("reading user-defined access methods");
	getAccessMethods(fout, &numAccessMethods);

	pg_log_info("reading user-defined operator classes");
	getOpclasses(fout, &numOpclasses);

	pg_log_info("reading user-defined operator families");
	getOpfamilies(fout, &numOpfamilies);

	pg_log_info("reading user-defined text search parsers");
	getTSParsers(fout, &numTSParsers);

	pg_log_info("reading user-defined text search templates");
	getTSTemplates(fout, &numTSTemplates);

	pg_log_info("reading user-defined text search dictionaries");
	getTSDictionaries(fout, &numTSDicts);

	pg_log_info("reading user-defined text search configurations");
	getTSConfigurations(fout, &numTSConfigs);

	pg_log_info("reading user-defined foreign-data wrappers");
	getForeignDataWrappers(fout, &numForeignDataWrappers);

	pg_log_info("reading user-defined foreign servers");
	getForeignServers(fout, &numForeignServers);

	pg_log_info("reading default privileges");
	getDefaultACLs(fout, &numDefaultACLs);

	pg_log_info("reading user-defined collations");
	collinfo = getCollations(fout, &numCollations);
	collinfoindex = buildIndexArray(collinfo, numCollations, sizeof(CollInfo));

	pg_log_info("reading user-defined conversions");
	getConversions(fout, &numConversions);

	pg_log_info("reading type casts");
	getCasts(fout, &numCasts);

	pg_log_info("reading transforms");
	getTransforms(fout, &numTransforms);

	pg_log_info("reading table inheritance information");
	inhinfo = getInherits(fout, &numInherits);

	pg_log_info("reading event triggers");
	getEventTriggers(fout, &numEventTriggers);

	/* Identify extension configuration tables that should be dumped */
	pg_log_info("finding extension tables");
	processExtensionTables(fout, extinfo, numExtensions);

	/* Link tables to parents, mark parents of target tables interesting */
	pg_log_info("finding inheritance relationships");
	flagInhTables(fout, tblinfo, numTables, inhinfo, numInherits);

	pg_log_info("reading column info for interesting tables");
	getTableAttrs(fout, tblinfo, numTables);

	pg_log_info("flagging inherited columns in subtables");
	flagInhAttrs(fout->dopt, tblinfo, numTables);

	pg_log_info("reading indexes");
	getIndexes(fout, tblinfo, numTables);

	pg_log_info("flagging indexes in partitioned tables");
	flagInhIndexes(fout, tblinfo, numTables);

	pg_log_info("reading extended statistics");
	getExtendedStatistics(fout);

	pg_log_info("reading constraints");
	getConstraints(fout, tblinfo, numTables);

	pg_log_info("reading triggers");
	getTriggers(fout, tblinfo, numTables);

	pg_log_info("reading rewrite rules");
	getRules(fout, &numRules);

	pg_log_info("reading policies");
	getPolicies(fout, tblinfo, numTables);

	pg_log_info("reading publications");
	getPublications(fout);

	pg_log_info("reading publication membership");
	getPublicationTables(fout, tblinfo, numTables);

	pg_log_info("reading subscriptions");
	getSubscriptions(fout);

	*numTablesPtr = numTables;
	return tblinfo;
}