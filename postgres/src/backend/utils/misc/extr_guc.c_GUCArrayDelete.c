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
struct config_generic {char* name; } ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (char const*) ; 
 int /*<<< orphan*/  TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  array_ref (int /*<<< orphan*/ *,int,int*,int,int,int,char,int*) ; 
 int /*<<< orphan*/ * array_set (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int,int,int,int,char) ; 
 int /*<<< orphan*/ * construct_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,char) ; 
 struct config_generic* find_option (char const*,int,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  validate_option_array_item (char const*,int /*<<< orphan*/ *,int) ; 

ArrayType *
GUCArrayDelete(ArrayType *array, const char *name)
{
	struct config_generic *record;
	ArrayType  *newarray;
	int			i;
	int			index;

	Assert(name);

	/* test if the option is valid and we're allowed to set it */
	(void) validate_option_array_item(name, NULL, false);

	/* normalize name (converts obsolete GUC names to modern spellings) */
	record = find_option(name, false, WARNING);
	if (record)
		name = record->name;

	/* if array is currently null, then surely nothing to delete */
	if (!array)
		return NULL;

	newarray = NULL;
	index = 1;

	for (i = 1; i <= ARR_DIMS(array)[0]; i++)
	{
		Datum		d;
		char	   *val;
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

		/* ignore entry if it's what we want to delete */
		if (strncmp(val, name, strlen(name)) == 0
			&& val[strlen(name)] == '=')
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
	}

	return newarray;
}