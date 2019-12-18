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
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ NodeTag ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  LEFT_BRACE 135 
#define  LEFT_PAREN 134 
 int /*<<< orphan*/ * NIL ; 
#define  OTHER_TOKEN 133 
#define  RIGHT_PAREN 132 
#define  T_BitString 131 
#define  T_Float 130 
#define  T_Integer 129 
#define  T_String 128 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  debackslash (char const*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * lappend_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ makeBitString (char*) ; 
 scalar_t__ makeFloat (char*) ; 
 scalar_t__ makeInteger (int /*<<< orphan*/ ) ; 
 scalar_t__ makeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ nodeTokenType (char const*,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/ * parseNodeString () ; 
 char* pg_strtok (int*) ; 
 scalar_t__ strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 

void *
nodeRead(const char *token, int tok_len)
{
	Node	   *result;
	NodeTag		type;

	if (token == NULL)			/* need to read a token? */
	{
		token = pg_strtok(&tok_len);

		if (token == NULL)		/* end of input */
			return NULL;
	}

	type = nodeTokenType(token, tok_len);

	switch ((int) type)
	{
		case LEFT_BRACE:
			result = parseNodeString();
			token = pg_strtok(&tok_len);
			if (token == NULL || token[0] != '}')
				elog(ERROR, "did not find '}' at end of input node");
			break;
		case LEFT_PAREN:
			{
				List	   *l = NIL;

				/*----------
				 * Could be an integer list:	(i int int ...)
				 * or an OID list:				(o int int ...)
				 * or a list of nodes/values:	(node node ...)
				 *----------
				 */
				token = pg_strtok(&tok_len);
				if (token == NULL)
					elog(ERROR, "unterminated List structure");
				if (tok_len == 1 && token[0] == 'i')
				{
					/* List of integers */
					for (;;)
					{
						int			val;
						char	   *endptr;

						token = pg_strtok(&tok_len);
						if (token == NULL)
							elog(ERROR, "unterminated List structure");
						if (token[0] == ')')
							break;
						val = (int) strtol(token, &endptr, 10);
						if (endptr != token + tok_len)
							elog(ERROR, "unrecognized integer: \"%.*s\"",
								 tok_len, token);
						l = lappend_int(l, val);
					}
				}
				else if (tok_len == 1 && token[0] == 'o')
				{
					/* List of OIDs */
					for (;;)
					{
						Oid			val;
						char	   *endptr;

						token = pg_strtok(&tok_len);
						if (token == NULL)
							elog(ERROR, "unterminated List structure");
						if (token[0] == ')')
							break;
						val = (Oid) strtoul(token, &endptr, 10);
						if (endptr != token + tok_len)
							elog(ERROR, "unrecognized OID: \"%.*s\"",
								 tok_len, token);
						l = lappend_oid(l, val);
					}
				}
				else
				{
					/* List of other node types */
					for (;;)
					{
						/* We have already scanned next token... */
						if (token[0] == ')')
							break;
						l = lappend(l, nodeRead(token, tok_len));
						token = pg_strtok(&tok_len);
						if (token == NULL)
							elog(ERROR, "unterminated List structure");
					}
				}
				result = (Node *) l;
				break;
			}
		case RIGHT_PAREN:
			elog(ERROR, "unexpected right parenthesis");
			result = NULL;		/* keep compiler happy */
			break;
		case OTHER_TOKEN:
			if (tok_len == 0)
			{
				/* must be "<>" --- represents a null pointer */
				result = NULL;
			}
			else
			{
				elog(ERROR, "unrecognized token: \"%.*s\"", tok_len, token);
				result = NULL;	/* keep compiler happy */
			}
			break;
		case T_Integer:

			/*
			 * we know that the token terminates on a char atoi will stop at
			 */
			result = (Node *) makeInteger(atoi(token));
			break;
		case T_Float:
			{
				char	   *fval = (char *) palloc(tok_len + 1);

				memcpy(fval, token, tok_len);
				fval[tok_len] = '\0';
				result = (Node *) makeFloat(fval);
			}
			break;
		case T_String:
			/* need to remove leading and trailing quotes, and backslashes */
			result = (Node *) makeString(debackslash(token + 1, tok_len - 2));
			break;
		case T_BitString:
			{
				char	   *val = palloc(tok_len);

				/* skip leading 'b' */
				memcpy(val, token + 1, tok_len - 1);
				val[tok_len - 1] = '\0';
				result = (Node *) makeBitString(val);
				break;
			}
		default:
			elog(ERROR, "unrecognized node type: %d", (int) type);
			result = NULL;		/* keep compiler happy */
			break;
	}

	return (void *) result;
}