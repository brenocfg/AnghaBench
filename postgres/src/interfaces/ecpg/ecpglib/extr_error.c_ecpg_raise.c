#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sqlerrmc; int /*<<< orphan*/  sqlerrml; } ;
struct sqlca_t {int sqlcode; TYPE_1__ sqlerrm; int /*<<< orphan*/  sqlstate; } ;

/* Variables and functions */
#define  ECPG_ARRAY_INSERT 151 
#define  ECPG_CONNECT 150 
#define  ECPG_CONVERT_BOOL 149 
#define  ECPG_DATA_NOT_ARRAY 148 
#define  ECPG_EMPTY 147 
#define  ECPG_FLOAT_FORMAT 146 
#define  ECPG_INT_FORMAT 145 
#define  ECPG_INVALID_DESCRIPTOR_INDEX 144 
#define  ECPG_INVALID_STMT 143 
#define  ECPG_MISSING_INDICATOR 142 
#define  ECPG_NOT_CONN 141 
#define  ECPG_NOT_FOUND 140 
#define  ECPG_NO_ARRAY 139 
#define  ECPG_NO_CONN 138 
#define  ECPG_OUT_OF_MEMORY 137 
#define  ECPG_TOO_FEW_ARGUMENTS 136 
#define  ECPG_TOO_MANY_ARGUMENTS 135 
#define  ECPG_TRANS 134 
#define  ECPG_UINT_FORMAT 133 
#define  ECPG_UNKNOWN_DESCRIPTOR 132 
#define  ECPG_UNKNOWN_DESCRIPTOR_ITEM 131 
#define  ECPG_UNSUPPORTED 130 
#define  ECPG_VAR_NOT_CHAR 129 
#define  ECPG_VAR_NOT_NUMERIC 128 
 int /*<<< orphan*/  ECPGfree_auto_mem () ; 
 struct sqlca_t* ECPGget_sqlca () ; 
 char* ecpg_gettext (char*) ; 
 int /*<<< orphan*/  ecpg_log (char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

void
ecpg_raise(int line, int code, const char *sqlstate, const char *str)
{
	struct sqlca_t *sqlca = ECPGget_sqlca();

	if (sqlca == NULL)
	{
		ecpg_log("out of memory");
		ECPGfree_auto_mem();
		return;
	}

	sqlca->sqlcode = code;
	strncpy(sqlca->sqlstate, sqlstate, sizeof(sqlca->sqlstate));

	switch (code)
	{
		case ECPG_NOT_FOUND:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("no data found on line %d"), line);
			break;

		case ECPG_OUT_OF_MEMORY:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("out of memory on line %d"), line);
			break;

		case ECPG_UNSUPPORTED:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("unsupported type \"%s\" on line %d"), str, line);
			break;

		case ECPG_TOO_MANY_ARGUMENTS:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("too many arguments on line %d"), line);
			break;

		case ECPG_TOO_FEW_ARGUMENTS:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("too few arguments on line %d"), line);
			break;

		case ECPG_INT_FORMAT:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("invalid input syntax for type int: \"%s\", on line %d"), str, line);
			break;

		case ECPG_UINT_FORMAT:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("invalid input syntax for type unsigned int: \"%s\", on line %d"), str, line);
			break;

		case ECPG_FLOAT_FORMAT:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("invalid input syntax for floating-point type: \"%s\", on line %d"), str, line);
			break;

		case ECPG_CONVERT_BOOL:
			if (str)
				snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
				/*------
				   translator: this string will be truncated at 149 characters expanded.  */
						 ecpg_gettext("invalid syntax for type boolean: \"%s\", on line %d"), str, line);
			else
				snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
				/*------
				   translator: this string will be truncated at 149 characters expanded.  */
						 ecpg_gettext("could not convert boolean value: size mismatch, on line %d"), line);
			break;

		case ECPG_EMPTY:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("empty query on line %d"), line);
			break;

		case ECPG_MISSING_INDICATOR:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("null value without indicator on line %d"), line);
			break;

		case ECPG_NO_ARRAY:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("variable does not have an array type on line %d"), line);
			break;

		case ECPG_DATA_NOT_ARRAY:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("data read from server is not an array on line %d"), line);
			break;

		case ECPG_ARRAY_INSERT:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("inserting an array of variables is not supported on line %d"), line);
			break;

		case ECPG_NO_CONN:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("connection \"%s\" does not exist on line %d"), str, line);
			break;

		case ECPG_NOT_CONN:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("not connected to connection \"%s\" on line %d"), str, line);
			break;

		case ECPG_INVALID_STMT:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("invalid statement name \"%s\" on line %d"), str, line);
			break;

		case ECPG_UNKNOWN_DESCRIPTOR:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("descriptor \"%s\" not found on line %d"), str, line);
			break;

		case ECPG_INVALID_DESCRIPTOR_INDEX:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("descriptor index out of range on line %d"), line);
			break;

		case ECPG_UNKNOWN_DESCRIPTOR_ITEM:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("unrecognized descriptor item \"%s\" on line %d"), str, line);
			break;

		case ECPG_VAR_NOT_NUMERIC:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("variable does not have a numeric type on line %d"), line);
			break;

		case ECPG_VAR_NOT_CHAR:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("variable does not have a character type on line %d"), line);
			break;

		case ECPG_TRANS:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("error in transaction processing on line %d"), line);
			break;

		case ECPG_CONNECT:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("could not connect to database \"%s\" on line %d"), str, line);
			break;

		default:
			snprintf(sqlca->sqlerrm.sqlerrmc, sizeof(sqlca->sqlerrm.sqlerrmc),
			/*------
			   translator: this string will be truncated at 149 characters expanded.  */
					 ecpg_gettext("SQL error %d on line %d"), code, line);
			break;
	}

	sqlca->sqlerrm.sqlerrml = strlen(sqlca->sqlerrm.sqlerrmc);
	ecpg_log("raising sqlcode %d on line %d: %s\n", code, line, sqlca->sqlerrm.sqlerrmc);

	/* free all memory we have allocated for the user */
	ECPGfree_auto_mem();
}