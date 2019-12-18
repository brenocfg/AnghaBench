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
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_ARRAY_SUBSCRIPT_ERROR ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char,int /*<<< orphan*/ **,int**,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  string_is_ascii (char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int
parse_key_value_arrays(ArrayType *key_array, ArrayType *val_array,
					   char ***p_keys, char ***p_values)
{
	int			nkdims = ARR_NDIM(key_array);
	int			nvdims = ARR_NDIM(val_array);
	char	  **keys,
			  **values;
	Datum	   *key_datums,
			   *val_datums;
	bool	   *key_nulls,
			   *val_nulls;
	int			key_count,
				val_count;
	int			i;

	if (nkdims > 1 || nkdims != nvdims)
		ereport(ERROR,
				(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
				 errmsg("wrong number of array subscripts")));
	if (nkdims == 0)
		return 0;

	deconstruct_array(key_array,
					  TEXTOID, -1, false, 'i',
					  &key_datums, &key_nulls, &key_count);

	deconstruct_array(val_array,
					  TEXTOID, -1, false, 'i',
					  &val_datums, &val_nulls, &val_count);

	if (key_count != val_count)
		ereport(ERROR,
				(errcode(ERRCODE_ARRAY_SUBSCRIPT_ERROR),
				 errmsg("mismatched array dimensions")));

	keys = (char **) palloc(sizeof(char *) * key_count);
	values = (char **) palloc(sizeof(char *) * val_count);

	for (i = 0; i < key_count; i++)
	{
		char	   *v;

		/* Check that the key doesn't contain anything funny */
		if (key_nulls[i])
			ereport(ERROR,
					(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
					 errmsg("null value not allowed for header key")));

		v = TextDatumGetCString(key_datums[i]);

		if (!string_is_ascii(v))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("header key must not contain non-ASCII characters")));
		if (strstr(v, ": "))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("header key must not contain \": \"")));
		if (strchr(v, '\n'))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("header key must not contain newlines")));
		keys[i] = v;

		/* And the same for the value */
		if (val_nulls[i])
			ereport(ERROR,
					(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
					 errmsg("null value not allowed for header value")));

		v = TextDatumGetCString(val_datums[i]);

		if (!string_is_ascii(v))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("header value must not contain non-ASCII characters")));
		if (strchr(v, '\n'))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("header value must not contain newlines")));

		values[i] = v;
	}

	*p_keys = keys;
	*p_values = values;
	return key_count;
}