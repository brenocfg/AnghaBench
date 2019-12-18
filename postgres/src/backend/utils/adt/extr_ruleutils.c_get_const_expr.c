#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_context ;
struct TYPE_8__ {int consttype; int /*<<< orphan*/  consttypmod; int /*<<< orphan*/  constvalue; scalar_t__ constisnull; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Const ;

/* Variables and functions */
#define  BOOLOID 131 
#define  INT4OID 130 
#define  NUMERICOID 129 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  UNKNOWNOID 128 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* format_type_with_typemod (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_const_collation (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  simple_quote_literal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
get_const_expr(Const *constval, deparse_context *context, int showtype)
{
	StringInfo	buf = context->buf;
	Oid			typoutput;
	bool		typIsVarlena;
	char	   *extval;
	bool		needlabel = false;

	if (constval->constisnull)
	{
		/*
		 * Always label the type of a NULL constant to prevent misdecisions
		 * about type when reparsing.
		 */
		appendStringInfoString(buf, "NULL");
		if (showtype >= 0)
		{
			appendStringInfo(buf, "::%s",
							 format_type_with_typemod(constval->consttype,
													  constval->consttypmod));
			get_const_collation(constval, context);
		}
		return;
	}

	getTypeOutputInfo(constval->consttype,
					  &typoutput, &typIsVarlena);

	extval = OidOutputFunctionCall(typoutput, constval->constvalue);

	switch (constval->consttype)
	{
		case INT4OID:

			/*
			 * INT4 can be printed without any decoration, unless it is
			 * negative; in that case print it as '-nnn'::integer to ensure
			 * that the output will re-parse as a constant, not as a constant
			 * plus operator.  In most cases we could get away with printing
			 * (-nnn) instead, because of the way that gram.y handles negative
			 * literals; but that doesn't work for INT_MIN, and it doesn't
			 * seem that much prettier anyway.
			 */
			if (extval[0] != '-')
				appendStringInfoString(buf, extval);
			else
			{
				appendStringInfo(buf, "'%s'", extval);
				needlabel = true;	/* we must attach a cast */
			}
			break;

		case NUMERICOID:

			/*
			 * NUMERIC can be printed without quotes if it looks like a float
			 * constant (not an integer, and not Infinity or NaN) and doesn't
			 * have a leading sign (for the same reason as for INT4).
			 */
			if (isdigit((unsigned char) extval[0]) &&
				strcspn(extval, "eE.") != strlen(extval))
			{
				appendStringInfoString(buf, extval);
			}
			else
			{
				appendStringInfo(buf, "'%s'", extval);
				needlabel = true;	/* we must attach a cast */
			}
			break;

		case BOOLOID:
			if (strcmp(extval, "t") == 0)
				appendStringInfoString(buf, "true");
			else
				appendStringInfoString(buf, "false");
			break;

		default:
			simple_quote_literal(buf, extval);
			break;
	}

	pfree(extval);

	if (showtype < 0)
		return;

	/*
	 * For showtype == 0, append ::typename unless the constant will be
	 * implicitly typed as the right type when it is read in.
	 *
	 * XXX this code has to be kept in sync with the behavior of the parser,
	 * especially make_const.
	 */
	switch (constval->consttype)
	{
		case BOOLOID:
		case UNKNOWNOID:
			/* These types can be left unlabeled */
			needlabel = false;
			break;
		case INT4OID:
			/* We determined above whether a label is needed */
			break;
		case NUMERICOID:

			/*
			 * Float-looking constants will be typed as numeric, which we
			 * checked above; but if there's a nondefault typmod we need to
			 * show it.
			 */
			needlabel |= (constval->consttypmod >= 0);
			break;
		default:
			needlabel = true;
			break;
	}
	if (needlabel || showtype > 0)
		appendStringInfo(buf, "::%s",
						 format_type_with_typemod(constval->consttype,
												  constval->consttypmod));

	get_const_collation(constval, context);
}