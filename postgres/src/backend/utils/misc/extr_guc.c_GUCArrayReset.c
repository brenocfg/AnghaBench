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
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref (int /*<<< orphan*/ *,int,int*,int,int,int,char,int*) ; 
 int /*<<< orphan*/ * array_set (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int,int,int,int,char) ; 
 int /*<<< orphan*/ * construct_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,char) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ superuser () ; 
 scalar_t__ validate_option_array_item (char*,int /*<<< orphan*/ *,int) ; 

ArrayType *
GUCArrayReset(ArrayType *array)
{
	ArrayType  *newarray;
	int			i;
	int			index;

	/* if array is currently null, nothing to do */
	if (!array)
		return NULL;

	/* if we're superuser, we can delete everything, so just do it */
	if (superuser())
		return NULL;

	newarray = NULL;
	index = 1;

	for (i = 1; i <= ARR_DIMS(array)[0]; i++)
	{
		Datum		d;
		char	   *val;
		char	   *eqsgn;
		bool		isnull;

		d = array_ref(array, 1, &i,
					  -1 /* varlenarray */ ,
					  -1 /* TEXT's typlen */ ,
					  false /* TEXT's typbyval */ ,
					  'i' /* TEXT's typalign */ ,
					  &isnull);
		if (isnull)
			continue;
		val = TextDatumGetCString(d);

		eqsgn = strchr(val, '=');
		*eqsgn = '\0';

		/* skip if we have permission to delete it */
		if (validate_option_array_item(val, NULL, true))
			continue;

		/* else add it to the output array */
		if (newarray)
			newarray = array_set(newarray, 1, &index,
								 d,
								 false,
								 -1 /* varlenarray */ ,
								 -1 /* TEXT's typlen */ ,
								 false /* TEXT's typbyval */ ,
								 'i' /* TEXT's typalign */ );
		else
			newarray = construct_array(&d, 1,
									   TEXTOID,
									   -1, false, 'i');

		index++;
		pfree(val);
	}

	return newarray;
}