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
struct variable {int arrsize; int ind_arrsize; int varcharsize; char* value; int const type; int offset; scalar_t__ ind_varcharsize; char* ind_value; int ind_offset; int /*<<< orphan*/  ind_type; int /*<<< orphan*/ * ind_pointer; scalar_t__ pointer; } ;
struct statement {int /*<<< orphan*/  force_indicator; int /*<<< orphan*/  compat; int /*<<< orphan*/  lineno; } ;
typedef  enum ARRAY_TYPE { ____Placeholder_ARRAY_TYPE } ARRAY_TYPE ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int ECPG_ARRAY_ERROR ; 
 int ECPG_ARRAY_NONE ; 
 int /*<<< orphan*/  ECPG_INFORMIX_SUBSELECT_NOT_ONE ; 
 int /*<<< orphan*/  ECPG_NO_ARRAY ; 
 int /*<<< orphan*/  ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_CARDINALITY_VIOLATION ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ECPG_TOO_MANY_MATCHES ; 
#define  ECPGt_char 131 
#define  ECPGt_string 130 
#define  ECPGt_unsigned_char 129 
#define  ECPGt_varchar 128 
 scalar_t__ INFORMIX_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfformat (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  PQftype (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ PQgetlength (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/  const*,int,int) ; 
 int PQntuples (int /*<<< orphan*/  const*) ; 
 scalar_t__ ecpg_auto_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_get_data (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,char*,char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecpg_is_type_an_array (int /*<<< orphan*/ ,struct statement const*,struct variable*) ; 
 int /*<<< orphan*/  ecpg_log (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ecpg_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 

bool
ecpg_store_result(const PGresult *results, int act_field,
				  const struct statement *stmt, struct variable *var)
{
	enum ARRAY_TYPE isarray;
	int			act_tuple,
				ntuples = PQntuples(results);
	bool		status = true;

	if ((isarray = ecpg_is_type_an_array(PQftype(results, act_field), stmt, var)) == ECPG_ARRAY_ERROR)
	{
		ecpg_raise(stmt->lineno, ECPG_OUT_OF_MEMORY, ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
		return false;
	}

	if (isarray == ECPG_ARRAY_NONE)
	{
		/*
		 * if we don't have enough space, we cannot read all tuples
		 */
		if ((var->arrsize > 0 && ntuples > var->arrsize) || (var->ind_arrsize > 0 && ntuples > var->ind_arrsize))
		{
			ecpg_log("ecpg_store_result on line %d: incorrect number of matches; %d don't fit into array of %ld\n",
					 stmt->lineno, ntuples, var->arrsize);
			ecpg_raise(stmt->lineno, INFORMIX_MODE(stmt->compat) ? ECPG_INFORMIX_SUBSELECT_NOT_ONE : ECPG_TOO_MANY_MATCHES, ECPG_SQLSTATE_CARDINALITY_VIOLATION, NULL);
			return false;
		}
	}
	else
	{
		/*
		 * since we read an array, the variable has to be an array too
		 */
		if (var->arrsize == 0)
		{
			ecpg_raise(stmt->lineno, ECPG_NO_ARRAY, ECPG_SQLSTATE_DATATYPE_MISMATCH, NULL);
			return false;
		}
	}

	/*
	 * allocate memory for NULL pointers
	 */
	if ((var->arrsize == 0 || var->varcharsize == 0) && var->value == NULL)
	{
		int			len = 0;

		if (!PQfformat(results, act_field))
		{
			switch (var->type)
			{
				case ECPGt_char:
				case ECPGt_unsigned_char:
				case ECPGt_string:
					if (!var->varcharsize && !var->arrsize)
					{
						/* special mode for handling char**foo=0 */
						for (act_tuple = 0; act_tuple < ntuples; act_tuple++)
							len += strlen(PQgetvalue(results, act_tuple, act_field)) + 1;
						len *= var->offset; /* should be 1, but YMNK */
						len += (ntuples + 1) * sizeof(char *);
					}
					else
					{
						var->varcharsize = 0;
						/* check strlen for each tuple */
						for (act_tuple = 0; act_tuple < ntuples; act_tuple++)
						{
							int			len = strlen(PQgetvalue(results, act_tuple, act_field)) + 1;

							if (len > var->varcharsize)
								var->varcharsize = len;
						}
						var->offset *= var->varcharsize;
						len = var->offset * ntuples;
					}
					break;
				case ECPGt_varchar:
					len = ntuples * (var->varcharsize + sizeof(int));
					break;
				default:
					len = var->offset * ntuples;
					break;
			}
		}
		else
		{
			for (act_tuple = 0; act_tuple < ntuples; act_tuple++)
				len += PQgetlength(results, act_tuple, act_field);
		}

		ecpg_log("ecpg_store_result on line %d: allocating memory for %d tuples\n", stmt->lineno, ntuples);
		var->value = (char *) ecpg_auto_alloc(len, stmt->lineno);
		if (!var->value)
			return false;
		*((char **) var->pointer) = var->value;
	}

	/* allocate indicator variable if needed */
	if ((var->ind_arrsize == 0 || var->ind_varcharsize == 0) && var->ind_value == NULL && var->ind_pointer != NULL)
	{
		int			len = var->ind_offset * ntuples;

		var->ind_value = (char *) ecpg_auto_alloc(len, stmt->lineno);
		if (!var->ind_value)
			return false;
		*((char **) var->ind_pointer) = var->ind_value;
	}

	/* fill the variable with the tuple(s) */
	if (!var->varcharsize && !var->arrsize &&
		(var->type == ECPGt_char || var->type == ECPGt_unsigned_char || var->type == ECPGt_string))
	{
		/* special mode for handling char**foo=0 */

		/* filling the array of (char*)s */
		char	  **current_string = (char **) var->value;

		/* storing the data (after the last array element) */
		char	   *current_data_location = (char *) &current_string[ntuples + 1];

		for (act_tuple = 0; act_tuple < ntuples && status; act_tuple++)
		{
			int			len = strlen(PQgetvalue(results, act_tuple, act_field)) + 1;

			if (!ecpg_get_data(results, act_tuple, act_field, stmt->lineno,
							   var->type, var->ind_type, current_data_location,
							   var->ind_value, len, 0, var->ind_offset, isarray, stmt->compat, stmt->force_indicator))
				status = false;
			else
			{
				*current_string = current_data_location;
				current_data_location += len;
				current_string++;
			}
		}

		/* terminate the list */
		*current_string = NULL;
	}
	else
	{
		for (act_tuple = 0; act_tuple < ntuples && status; act_tuple++)
		{
			if (!ecpg_get_data(results, act_tuple, act_field, stmt->lineno,
							   var->type, var->ind_type, var->value,
							   var->ind_value, var->varcharsize, var->offset, var->ind_offset, isarray, stmt->compat, stmt->force_indicator))
				status = false;
		}
	}
	return status;
}