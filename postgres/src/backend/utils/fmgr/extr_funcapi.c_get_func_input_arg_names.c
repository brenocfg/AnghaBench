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
typedef  scalar_t__ Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_HASNULL (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ CHAROID ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 char PROARGMODE_IN ; 
 char PROARGMODE_INOUT ; 
 char PROARGMODE_VARIADIC ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ TEXTOID ; 
 char* TextDatumGetCString (scalar_t__) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,scalar_t__,int,int,char,scalar_t__**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ palloc (int) ; 

int
get_func_input_arg_names(Datum proargnames, Datum proargmodes,
						 char ***arg_names)
{
	ArrayType  *arr;
	int			numargs;
	Datum	   *argnames;
	char	   *argmodes;
	char	  **inargnames;
	int			numinargs;
	int			i;

	/* Do nothing if null proargnames */
	if (proargnames == PointerGetDatum(NULL))
	{
		*arg_names = NULL;
		return 0;
	}

	/*
	 * We expect the arrays to be 1-D arrays of the right types; verify that.
	 * For proargmodes, we don't need to use deconstruct_array() since the
	 * array data is just going to look like a C array of values.
	 */
	arr = DatumGetArrayTypeP(proargnames);	/* ensure not toasted */
	if (ARR_NDIM(arr) != 1 ||
		ARR_HASNULL(arr) ||
		ARR_ELEMTYPE(arr) != TEXTOID)
		elog(ERROR, "proargnames is not a 1-D text array");
	deconstruct_array(arr, TEXTOID, -1, false, 'i',
					  &argnames, NULL, &numargs);
	if (proargmodes != PointerGetDatum(NULL))
	{
		arr = DatumGetArrayTypeP(proargmodes);	/* ensure not toasted */
		if (ARR_NDIM(arr) != 1 ||
			ARR_DIMS(arr)[0] != numargs ||
			ARR_HASNULL(arr) ||
			ARR_ELEMTYPE(arr) != CHAROID)
			elog(ERROR, "proargmodes is not a 1-D char array");
		argmodes = (char *) ARR_DATA_PTR(arr);
	}
	else
		argmodes = NULL;

	/* zero elements probably shouldn't happen, but handle it gracefully */
	if (numargs <= 0)
	{
		*arg_names = NULL;
		return 0;
	}

	/* extract input-argument names */
	inargnames = (char **) palloc(numargs * sizeof(char *));
	numinargs = 0;
	for (i = 0; i < numargs; i++)
	{
		if (argmodes == NULL ||
			argmodes[i] == PROARGMODE_IN ||
			argmodes[i] == PROARGMODE_INOUT ||
			argmodes[i] == PROARGMODE_VARIADIC)
		{
			char	   *pname = TextDatumGetCString(argnames[i]);

			if (pname[0] != '\0')
				inargnames[numinargs] = pname;
			else
				inargnames[numinargs] = NULL;
			numinargs++;
		}
	}

	*arg_names = inargnames;
	return numinargs;
}