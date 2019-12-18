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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeDefElem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ makeString (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 
 int /*<<< orphan*/  text_to_cstring (int /*<<< orphan*/ *) ; 

List *
deserialize_deflist(Datum txt)
{
	text	   *in = DatumGetTextPP(txt);	/* in case it's toasted */
	List	   *result = NIL;
	int			len = VARSIZE_ANY_EXHDR(in);
	char	   *ptr,
			   *endptr,
			   *workspace,
			   *wsptr = NULL,
			   *startvalue = NULL;
	typedef enum
	{
		CS_WAITKEY,
		CS_INKEY,
		CS_INQKEY,
		CS_WAITEQ,
		CS_WAITVALUE,
		CS_INSQVALUE,
		CS_INDQVALUE,
		CS_INWVALUE
	} ds_state;
	ds_state	state = CS_WAITKEY;

	workspace = (char *) palloc(len + 1);	/* certainly enough room */
	ptr = VARDATA_ANY(in);
	endptr = ptr + len;
	for (; ptr < endptr; ptr++)
	{
		switch (state)
		{
			case CS_WAITKEY:
				if (isspace((unsigned char) *ptr) || *ptr == ',')
					continue;
				if (*ptr == '"')
				{
					wsptr = workspace;
					state = CS_INQKEY;
				}
				else
				{
					wsptr = workspace;
					*wsptr++ = *ptr;
					state = CS_INKEY;
				}
				break;
			case CS_INKEY:
				if (isspace((unsigned char) *ptr))
				{
					*wsptr++ = '\0';
					state = CS_WAITEQ;
				}
				else if (*ptr == '=')
				{
					*wsptr++ = '\0';
					state = CS_WAITVALUE;
				}
				else
				{
					*wsptr++ = *ptr;
				}
				break;
			case CS_INQKEY:
				if (*ptr == '"')
				{
					if (ptr + 1 < endptr && ptr[1] == '"')
					{
						/* copy only one of the two quotes */
						*wsptr++ = *ptr++;
					}
					else
					{
						*wsptr++ = '\0';
						state = CS_WAITEQ;
					}
				}
				else
				{
					*wsptr++ = *ptr;
				}
				break;
			case CS_WAITEQ:
				if (*ptr == '=')
					state = CS_WAITVALUE;
				else if (!isspace((unsigned char) *ptr))
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("invalid parameter list format: \"%s\"",
									text_to_cstring(in))));
				break;
			case CS_WAITVALUE:
				if (*ptr == '\'')
				{
					startvalue = wsptr;
					state = CS_INSQVALUE;
				}
				else if (*ptr == 'E' && ptr + 1 < endptr && ptr[1] == '\'')
				{
					ptr++;
					startvalue = wsptr;
					state = CS_INSQVALUE;
				}
				else if (*ptr == '"')
				{
					startvalue = wsptr;
					state = CS_INDQVALUE;
				}
				else if (!isspace((unsigned char) *ptr))
				{
					startvalue = wsptr;
					*wsptr++ = *ptr;
					state = CS_INWVALUE;
				}
				break;
			case CS_INSQVALUE:
				if (*ptr == '\'')
				{
					if (ptr + 1 < endptr && ptr[1] == '\'')
					{
						/* copy only one of the two quotes */
						*wsptr++ = *ptr++;
					}
					else
					{
						*wsptr++ = '\0';
						result = lappend(result,
										 makeDefElem(pstrdup(workspace),
													 (Node *) makeString(pstrdup(startvalue)), -1));
						state = CS_WAITKEY;
					}
				}
				else if (*ptr == '\\')
				{
					if (ptr + 1 < endptr && ptr[1] == '\\')
					{
						/* copy only one of the two backslashes */
						*wsptr++ = *ptr++;
					}
					else
						*wsptr++ = *ptr;
				}
				else
				{
					*wsptr++ = *ptr;
				}
				break;
			case CS_INDQVALUE:
				if (*ptr == '"')
				{
					if (ptr + 1 < endptr && ptr[1] == '"')
					{
						/* copy only one of the two quotes */
						*wsptr++ = *ptr++;
					}
					else
					{
						*wsptr++ = '\0';
						result = lappend(result,
										 makeDefElem(pstrdup(workspace),
													 (Node *) makeString(pstrdup(startvalue)), -1));
						state = CS_WAITKEY;
					}
				}
				else
				{
					*wsptr++ = *ptr;
				}
				break;
			case CS_INWVALUE:
				if (*ptr == ',' || isspace((unsigned char) *ptr))
				{
					*wsptr++ = '\0';
					result = lappend(result,
									 makeDefElem(pstrdup(workspace),
												 (Node *) makeString(pstrdup(startvalue)), -1));
					state = CS_WAITKEY;
				}
				else
				{
					*wsptr++ = *ptr;
				}
				break;
			default:
				elog(ERROR, "unrecognized deserialize_deflist state: %d",
					 state);
		}
	}

	if (state == CS_INWVALUE)
	{
		*wsptr++ = '\0';
		result = lappend(result,
						 makeDefElem(pstrdup(workspace),
									 (Node *) makeString(pstrdup(startvalue)), -1));
	}
	else if (state != CS_WAITKEY)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("invalid parameter list format: \"%s\"",
						text_to_cstring(in))));

	pfree(workspace);

	return result;
}