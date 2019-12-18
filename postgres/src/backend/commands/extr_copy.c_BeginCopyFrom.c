#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int int32 ;
typedef  scalar_t__ copy_data_source_cb ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_18__ {int reached_eof; int line_buf_converted; char* raw_buf; int* defmap; int volatile_defexprs; int num_defaults; int is_program; int max_fields; char** raw_fields; int /*<<< orphan*/  attnumlist; scalar_t__ binary; int /*<<< orphan*/  filename; int /*<<< orphan*/ * copy_file; scalar_t__ data_source_cb; int /*<<< orphan*/  copy_dest; int /*<<< orphan*/ ** defexprs; int /*<<< orphan*/ * typioparams; int /*<<< orphan*/ * in_functions; int /*<<< orphan*/  rel; int /*<<< orphan*/  range_table; scalar_t__ raw_buf_len; scalar_t__ raw_buf_index; int /*<<< orphan*/  line_buf; int /*<<< orphan*/  attribute_buf; int /*<<< orphan*/ * cur_attval; int /*<<< orphan*/ * cur_attname; scalar_t__ cur_lineno; int /*<<< orphan*/  cur_relname; int /*<<< orphan*/  eol_type; int /*<<< orphan*/  copycontext; } ;
struct TYPE_17__ {int /*<<< orphan*/  attgenerated; int /*<<< orphan*/  atttypid; scalar_t__ attisdropped; } ;
struct TYPE_16__ {int /*<<< orphan*/  p_rtable; } ;
struct TYPE_15__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ ParseState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_4__* CopyState ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_4__* BeginCopy (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BinarySignature ; 
 int /*<<< orphan*/  COPY_CALLBACK ; 
 int CopyGetData (TYPE_4__*,char*,int,int) ; 
 int /*<<< orphan*/  CopyGetInt32 (TYPE_4__*,int*) ; 
 scalar_t__ DestRemote ; 
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  EOL_UNKNOWN ; 
 int /*<<< orphan*/  ERRCODE_BAD_COPY_FILE_FORMAT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExecInitExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenPipeStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_BINARY_R ; 
 int RAW_BUF_SIZE ; 
 int /*<<< orphan*/  ReceiveCopyBegin (TYPE_4__*) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ build_column_default (int /*<<< orphan*/ ,int) ; 
 int contain_volatile_functions_not_nextval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/ * expression_planner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  getTypeBinaryInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_member_int (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ whereToSendOutput ; 

CopyState
BeginCopyFrom(ParseState *pstate,
			  Relation rel,
			  const char *filename,
			  bool is_program,
			  copy_data_source_cb data_source_cb,
			  List *attnamelist,
			  List *options)
{
	CopyState	cstate;
	bool		pipe = (filename == NULL);
	TupleDesc	tupDesc;
	AttrNumber	num_phys_attrs,
				num_defaults;
	FmgrInfo   *in_functions;
	Oid		   *typioparams;
	int			attnum;
	Oid			in_func_oid;
	int		   *defmap;
	ExprState **defexprs;
	MemoryContext oldcontext;
	bool		volatile_defexprs;

	cstate = BeginCopy(pstate, true, rel, NULL, InvalidOid, attnamelist, options);
	oldcontext = MemoryContextSwitchTo(cstate->copycontext);

	/* Initialize state variables */
	cstate->reached_eof = false;
	cstate->eol_type = EOL_UNKNOWN;
	cstate->cur_relname = RelationGetRelationName(cstate->rel);
	cstate->cur_lineno = 0;
	cstate->cur_attname = NULL;
	cstate->cur_attval = NULL;

	/* Set up variables to avoid per-attribute overhead. */
	initStringInfo(&cstate->attribute_buf);
	initStringInfo(&cstate->line_buf);
	cstate->line_buf_converted = false;
	cstate->raw_buf = (char *) palloc(RAW_BUF_SIZE + 1);
	cstate->raw_buf_index = cstate->raw_buf_len = 0;

	/* Assign range table, we'll need it in CopyFrom. */
	if (pstate)
		cstate->range_table = pstate->p_rtable;

	tupDesc = RelationGetDescr(cstate->rel);
	num_phys_attrs = tupDesc->natts;
	num_defaults = 0;
	volatile_defexprs = false;

	/*
	 * Pick up the required catalog information for each attribute in the
	 * relation, including the input function, the element type (to pass to
	 * the input function), and info about defaults and constraints. (Which
	 * input function we use depends on text/binary format choice.)
	 */
	in_functions = (FmgrInfo *) palloc(num_phys_attrs * sizeof(FmgrInfo));
	typioparams = (Oid *) palloc(num_phys_attrs * sizeof(Oid));
	defmap = (int *) palloc(num_phys_attrs * sizeof(int));
	defexprs = (ExprState **) palloc(num_phys_attrs * sizeof(ExprState *));

	for (attnum = 1; attnum <= num_phys_attrs; attnum++)
	{
		Form_pg_attribute att = TupleDescAttr(tupDesc, attnum - 1);

		/* We don't need info for dropped attributes */
		if (att->attisdropped)
			continue;

		/* Fetch the input function and typioparam info */
		if (cstate->binary)
			getTypeBinaryInputInfo(att->atttypid,
								   &in_func_oid, &typioparams[attnum - 1]);
		else
			getTypeInputInfo(att->atttypid,
							 &in_func_oid, &typioparams[attnum - 1]);
		fmgr_info(in_func_oid, &in_functions[attnum - 1]);

		/* Get default info if needed */
		if (!list_member_int(cstate->attnumlist, attnum) && !att->attgenerated)
		{
			/* attribute is NOT to be copied from input */
			/* use default value if one exists */
			Expr	   *defexpr = (Expr *) build_column_default(cstate->rel,
																attnum);

			if (defexpr != NULL)
			{
				/* Run the expression through planner */
				defexpr = expression_planner(defexpr);

				/* Initialize executable expression in copycontext */
				defexprs[num_defaults] = ExecInitExpr(defexpr, NULL);
				defmap[num_defaults] = attnum - 1;
				num_defaults++;

				/*
				 * If a default expression looks at the table being loaded,
				 * then it could give the wrong answer when using
				 * multi-insert. Since database access can be dynamic this is
				 * hard to test for exactly, so we use the much wider test of
				 * whether the default expression is volatile. We allow for
				 * the special case of when the default expression is the
				 * nextval() of a sequence which in this specific case is
				 * known to be safe for use with the multi-insert
				 * optimization. Hence we use this special case function
				 * checker rather than the standard check for
				 * contain_volatile_functions().
				 */
				if (!volatile_defexprs)
					volatile_defexprs = contain_volatile_functions_not_nextval((Node *) defexpr);
			}
		}
	}

	/* We keep those variables in cstate. */
	cstate->in_functions = in_functions;
	cstate->typioparams = typioparams;
	cstate->defmap = defmap;
	cstate->defexprs = defexprs;
	cstate->volatile_defexprs = volatile_defexprs;
	cstate->num_defaults = num_defaults;
	cstate->is_program = is_program;

	if (data_source_cb)
	{
		cstate->copy_dest = COPY_CALLBACK;
		cstate->data_source_cb = data_source_cb;
	}
	else if (pipe)
	{
		Assert(!is_program);	/* the grammar does not allow this */
		if (whereToSendOutput == DestRemote)
			ReceiveCopyBegin(cstate);
		else
			cstate->copy_file = stdin;
	}
	else
	{
		cstate->filename = pstrdup(filename);

		if (cstate->is_program)
		{
			cstate->copy_file = OpenPipeStream(cstate->filename, PG_BINARY_R);
			if (cstate->copy_file == NULL)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not execute command \"%s\": %m",
								cstate->filename)));
		}
		else
		{
			struct stat st;

			cstate->copy_file = AllocateFile(cstate->filename, PG_BINARY_R);
			if (cstate->copy_file == NULL)
			{
				/* copy errno because ereport subfunctions might change it */
				int			save_errno = errno;

				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not open file \"%s\" for reading: %m",
								cstate->filename),
						 (save_errno == ENOENT || save_errno == EACCES) ?
						 errhint("COPY FROM instructs the PostgreSQL server process to read a file. "
								 "You may want a client-side facility such as psql's \\copy.") : 0));
			}

			if (fstat(fileno(cstate->copy_file), &st))
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not stat file \"%s\": %m",
								cstate->filename)));

			if (S_ISDIR(st.st_mode))
				ereport(ERROR,
						(errcode(ERRCODE_WRONG_OBJECT_TYPE),
						 errmsg("\"%s\" is a directory", cstate->filename)));
		}
	}

	if (cstate->binary)
	{
		/* Read and verify binary header */
		char		readSig[11];
		int32		tmp;

		/* Signature */
		if (CopyGetData(cstate, readSig, 11, 11) != 11 ||
			memcmp(readSig, BinarySignature, 11) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
					 errmsg("COPY file signature not recognized")));
		/* Flags field */
		if (!CopyGetInt32(cstate, &tmp))
			ereport(ERROR,
					(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
					 errmsg("invalid COPY file header (missing flags)")));
		if ((tmp & (1 << 16)) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
					 errmsg("invalid COPY file header (WITH OIDS)")));
		tmp &= ~(1 << 16);
		if ((tmp >> 16) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
					 errmsg("unrecognized critical flags in COPY file header")));
		/* Header extension length */
		if (!CopyGetInt32(cstate, &tmp) ||
			tmp < 0)
			ereport(ERROR,
					(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
					 errmsg("invalid COPY file header (missing length)")));
		/* Skip extension header, if present */
		while (tmp-- > 0)
		{
			if (CopyGetData(cstate, readSig, 1, 1) != 1)
				ereport(ERROR,
						(errcode(ERRCODE_BAD_COPY_FILE_FORMAT),
						 errmsg("invalid COPY file header (wrong length)")));
		}
	}

	/* create workspace for CopyReadAttributes results */
	if (!cstate->binary)
	{
		AttrNumber	attr_count = list_length(cstate->attnumlist);

		cstate->max_fields = attr_count;
		cstate->raw_fields = (char **) palloc(attr_count * sizeof(char *));
	}

	MemoryContextSwitchTo(oldcontext);

	return cstate;
}