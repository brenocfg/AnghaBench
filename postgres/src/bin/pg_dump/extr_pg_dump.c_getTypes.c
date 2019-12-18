#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {void* oid; void* tableoid; } ;
struct TYPE_24__ {void** name; int dump; int /*<<< orphan*/  namespace; TYPE_8__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_23__ {scalar_t__ typtype; int isDefined; int isArray; TYPE_22__ dobj; void* rolname; TYPE_2__* shellType; int /*<<< orphan*/ * domChecks; scalar_t__ nDomChecks; void* typrelkind; void* typrelid; void* typelem; void* initrtypacl; void* inittypacl; void* rtypacl; void* typacl; } ;
typedef  TYPE_1__ TypeInfo ;
struct TYPE_28__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_27__ {int /*<<< orphan*/  binary_upgrade; } ;
struct TYPE_26__ {int /*<<< orphan*/  data; } ;
struct TYPE_25__ {TYPE_22__ dobj; TYPE_1__* baseType; } ;
typedef  TYPE_2__ ShellTypeInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_22__*) ; 
 int /*<<< orphan*/  DO_SHELL_TYPE ; 
 int /*<<< orphan*/  DO_TYPE ; 
 int DUMP_COMPONENT_ACL ; 
 int DUMP_COMPONENT_DEFINITION ; 
 int DUMP_COMPONENT_NONE ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 void** PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPTYPE_BASE ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 scalar_t__ TYPTYPE_RANGE ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ,...) ; 
 void* atooid (void**) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  findNamespace (TYPE_5__*,void*) ; 
 int /*<<< orphan*/  getDomainConstraints (TYPE_5__*,TYPE_1__*) ; 
 TYPE_8__ nilCatalogId ; 
 int /*<<< orphan*/  pg_log_warning (char*,void**) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (void**) ; 
 int /*<<< orphan*/  selectDumpableType (TYPE_1__*,TYPE_5__*) ; 
 scalar_t__ strcmp (void**,char*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

TypeInfo *
getTypes(Archive *fout, int *numTypes)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	TypeInfo   *tyinfo;
	ShellTypeInfo *stinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_typname;
	int			i_typnamespace;
	int			i_typacl;
	int			i_rtypacl;
	int			i_inittypacl;
	int			i_initrtypacl;
	int			i_rolname;
	int			i_typelem;
	int			i_typrelid;
	int			i_typrelkind;
	int			i_typtype;
	int			i_typisdefined;
	int			i_isarray;

	/*
	 * we include even the built-in types because those may be used as array
	 * elements by user-defined types
	 *
	 * we filter out the built-in types when we dump out the types
	 *
	 * same approach for undefined (shell) types and array types
	 *
	 * Note: as of 8.3 we can reliably detect whether a type is an
	 * auto-generated array type by checking the element type's typarray.
	 * (Before that the test is capable of generating false positives.) We
	 * still check for name beginning with '_', though, so as to avoid the
	 * cost of the subselect probe for all standard types.  This would have to
	 * be revisited if the backend ever allows renaming of array types.
	 */

	if (fout->remoteVersion >= 90600)
	{
		PQExpBuffer acl_subquery = createPQExpBuffer();
		PQExpBuffer racl_subquery = createPQExpBuffer();
		PQExpBuffer initacl_subquery = createPQExpBuffer();
		PQExpBuffer initracl_subquery = createPQExpBuffer();

		buildACLQueries(acl_subquery, racl_subquery, initacl_subquery,
						initracl_subquery, "t.typacl", "t.typowner", "'T'",
						dopt->binary_upgrade);

		appendPQExpBuffer(query, "SELECT t.tableoid, t.oid, t.typname, "
						  "t.typnamespace, "
						  "%s AS typacl, "
						  "%s AS rtypacl, "
						  "%s AS inittypacl, "
						  "%s AS initrtypacl, "
						  "(%s t.typowner) AS rolname, "
						  "t.typelem, t.typrelid, "
						  "CASE WHEN t.typrelid = 0 THEN ' '::\"char\" "
						  "ELSE (SELECT relkind FROM pg_class WHERE oid = t.typrelid) END AS typrelkind, "
						  "t.typtype, t.typisdefined, "
						  "t.typname[0] = '_' AND t.typelem != 0 AND "
						  "(SELECT typarray FROM pg_type te WHERE oid = t.typelem) = t.oid AS isarray "
						  "FROM pg_type t "
						  "LEFT JOIN pg_init_privs pip ON "
						  "(t.oid = pip.objoid "
						  "AND pip.classoid = 'pg_type'::regclass "
						  "AND pip.objsubid = 0) ",
						  acl_subquery->data,
						  racl_subquery->data,
						  initacl_subquery->data,
						  initracl_subquery->data,
						  username_subquery);

		destroyPQExpBuffer(acl_subquery);
		destroyPQExpBuffer(racl_subquery);
		destroyPQExpBuffer(initacl_subquery);
		destroyPQExpBuffer(initracl_subquery);
	}
	else if (fout->remoteVersion >= 90200)
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, typname, "
						  "typnamespace, typacl, NULL as rtypacl, "
						  "NULL AS inittypacl, NULL AS initrtypacl, "
						  "(%s typowner) AS rolname, "
						  "typelem, typrelid, "
						  "CASE WHEN typrelid = 0 THEN ' '::\"char\" "
						  "ELSE (SELECT relkind FROM pg_class WHERE oid = typrelid) END AS typrelkind, "
						  "typtype, typisdefined, "
						  "typname[0] = '_' AND typelem != 0 AND "
						  "(SELECT typarray FROM pg_type te WHERE oid = pg_type.typelem) = oid AS isarray "
						  "FROM pg_type",
						  username_subquery);
	}
	else if (fout->remoteVersion >= 80300)
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, typname, "
						  "typnamespace, NULL AS typacl, NULL as rtypacl, "
						  "NULL AS inittypacl, NULL AS initrtypacl, "
						  "(%s typowner) AS rolname, "
						  "typelem, typrelid, "
						  "CASE WHEN typrelid = 0 THEN ' '::\"char\" "
						  "ELSE (SELECT relkind FROM pg_class WHERE oid = typrelid) END AS typrelkind, "
						  "typtype, typisdefined, "
						  "typname[0] = '_' AND typelem != 0 AND "
						  "(SELECT typarray FROM pg_type te WHERE oid = pg_type.typelem) = oid AS isarray "
						  "FROM pg_type",
						  username_subquery);
	}
	else
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, typname, "
						  "typnamespace, NULL AS typacl, NULL as rtypacl, "
						  "NULL AS inittypacl, NULL AS initrtypacl, "
						  "(%s typowner) AS rolname, "
						  "typelem, typrelid, "
						  "CASE WHEN typrelid = 0 THEN ' '::\"char\" "
						  "ELSE (SELECT relkind FROM pg_class WHERE oid = typrelid) END AS typrelkind, "
						  "typtype, typisdefined, "
						  "typname[0] = '_' AND typelem != 0 AS isarray "
						  "FROM pg_type",
						  username_subquery);
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	tyinfo = (TypeInfo *) pg_malloc(ntups * sizeof(TypeInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_typname = PQfnumber(res, "typname");
	i_typnamespace = PQfnumber(res, "typnamespace");
	i_typacl = PQfnumber(res, "typacl");
	i_rtypacl = PQfnumber(res, "rtypacl");
	i_inittypacl = PQfnumber(res, "inittypacl");
	i_initrtypacl = PQfnumber(res, "initrtypacl");
	i_rolname = PQfnumber(res, "rolname");
	i_typelem = PQfnumber(res, "typelem");
	i_typrelid = PQfnumber(res, "typrelid");
	i_typrelkind = PQfnumber(res, "typrelkind");
	i_typtype = PQfnumber(res, "typtype");
	i_typisdefined = PQfnumber(res, "typisdefined");
	i_isarray = PQfnumber(res, "isarray");

	for (i = 0; i < ntups; i++)
	{
		tyinfo[i].dobj.objType = DO_TYPE;
		tyinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		tyinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&tyinfo[i].dobj);
		tyinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_typname));
		tyinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_typnamespace)));
		tyinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		tyinfo[i].typacl = pg_strdup(PQgetvalue(res, i, i_typacl));
		tyinfo[i].rtypacl = pg_strdup(PQgetvalue(res, i, i_rtypacl));
		tyinfo[i].inittypacl = pg_strdup(PQgetvalue(res, i, i_inittypacl));
		tyinfo[i].initrtypacl = pg_strdup(PQgetvalue(res, i, i_initrtypacl));
		tyinfo[i].typelem = atooid(PQgetvalue(res, i, i_typelem));
		tyinfo[i].typrelid = atooid(PQgetvalue(res, i, i_typrelid));
		tyinfo[i].typrelkind = *PQgetvalue(res, i, i_typrelkind);
		tyinfo[i].typtype = *PQgetvalue(res, i, i_typtype);
		tyinfo[i].shellType = NULL;

		if (strcmp(PQgetvalue(res, i, i_typisdefined), "t") == 0)
			tyinfo[i].isDefined = true;
		else
			tyinfo[i].isDefined = false;

		if (strcmp(PQgetvalue(res, i, i_isarray), "t") == 0)
			tyinfo[i].isArray = true;
		else
			tyinfo[i].isArray = false;

		/* Decide whether we want to dump it */
		selectDumpableType(&tyinfo[i], fout);

		/* Do not try to dump ACL if no ACL exists. */
		if (PQgetisnull(res, i, i_typacl) && PQgetisnull(res, i, i_rtypacl) &&
			PQgetisnull(res, i, i_inittypacl) &&
			PQgetisnull(res, i, i_initrtypacl))
			tyinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;

		/*
		 * If it's a domain, fetch info about its constraints, if any
		 */
		tyinfo[i].nDomChecks = 0;
		tyinfo[i].domChecks = NULL;
		if ((tyinfo[i].dobj.dump & DUMP_COMPONENT_DEFINITION) &&
			tyinfo[i].typtype == TYPTYPE_DOMAIN)
			getDomainConstraints(fout, &(tyinfo[i]));

		/*
		 * If it's a base type, make a DumpableObject representing a shell
		 * definition of the type.  We will need to dump that ahead of the I/O
		 * functions for the type.  Similarly, range types need a shell
		 * definition in case they have a canonicalize function.
		 *
		 * Note: the shell type doesn't have a catId.  You might think it
		 * should copy the base type's catId, but then it might capture the
		 * pg_depend entries for the type, which we don't want.
		 */
		if ((tyinfo[i].dobj.dump & DUMP_COMPONENT_DEFINITION) &&
			(tyinfo[i].typtype == TYPTYPE_BASE ||
			 tyinfo[i].typtype == TYPTYPE_RANGE))
		{
			stinfo = (ShellTypeInfo *) pg_malloc(sizeof(ShellTypeInfo));
			stinfo->dobj.objType = DO_SHELL_TYPE;
			stinfo->dobj.catId = nilCatalogId;
			AssignDumpId(&stinfo->dobj);
			stinfo->dobj.name = pg_strdup(tyinfo[i].dobj.name);
			stinfo->dobj.namespace = tyinfo[i].dobj.namespace;
			stinfo->baseType = &(tyinfo[i]);
			tyinfo[i].shellType = stinfo;

			/*
			 * Initially mark the shell type as not to be dumped.  We'll only
			 * dump it if the I/O or canonicalize functions need to be dumped;
			 * this is taken care of while sorting dependencies.
			 */
			stinfo->dobj.dump = DUMP_COMPONENT_NONE;
		}

		if (strlen(tyinfo[i].rolname) == 0)
			pg_log_warning("owner of data type \"%s\" appears to be invalid",
						   tyinfo[i].dobj.name);
	}

	*numTypes = ntups;

	PQclear(res);

	destroyPQExpBuffer(query);

	return tyinfo;
}