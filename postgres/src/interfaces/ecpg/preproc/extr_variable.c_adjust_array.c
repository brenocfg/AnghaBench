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
typedef  enum ECPGttype { ____Placeholder_ECPGttype } ECPGttype ;

/* Variables and functions */
#define  ECPGt_bytea 134 
#define  ECPGt_char 133 
#define  ECPGt_string 132 
#define  ECPGt_struct 131 
#define  ECPGt_union 130 
#define  ECPGt_unsigned_char 129 
#define  ECPGt_varchar 128 
 int /*<<< orphan*/  PARSE_ERROR ; 
 scalar_t__ atoi (char*) ; 
 char* mm_strdup (char*) ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngettext (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void
adjust_array(enum ECPGttype type_enum, char **dimension, char **length, char *type_dimension, char *type_index, int pointer_len, bool type_definition)
{
	if (atoi(type_index) >= 0)
	{
		if (atoi(*length) >= 0)
			mmfatal(PARSE_ERROR, "multidimensional arrays are not supported");

		*length = type_index;
	}

	if (atoi(type_dimension) >= 0)
	{
		if (atoi(*dimension) >= 0 && atoi(*length) >= 0)
			mmfatal(PARSE_ERROR, "multidimensional arrays are not supported");

		if (atoi(*dimension) >= 0)
			*length = *dimension;

		*dimension = type_dimension;
	}

	if (pointer_len > 2)
		mmfatal(PARSE_ERROR, ngettext("multilevel pointers (more than 2 levels) are not supported; found %d level",
									  "multilevel pointers (more than 2 levels) are not supported; found %d levels", pointer_len),
				pointer_len);

	if (pointer_len > 1 && type_enum != ECPGt_char && type_enum != ECPGt_unsigned_char && type_enum != ECPGt_string)
		mmfatal(PARSE_ERROR, "pointer to pointer is not supported for this data type");

	if (pointer_len > 1 && (atoi(*length) >= 0 || atoi(*dimension) >= 0))
		mmfatal(PARSE_ERROR, "multidimensional arrays are not supported");

	if (atoi(*length) >= 0 && atoi(*dimension) >= 0 && pointer_len)
		mmfatal(PARSE_ERROR, "multidimensional arrays are not supported");

	switch (type_enum)
	{
		case ECPGt_struct:
		case ECPGt_union:
			/* pointer has to get dimension 0 */
			if (pointer_len)
			{
				*length = *dimension;
				*dimension = mm_strdup("0");
			}

			if (atoi(*length) >= 0)
				mmfatal(PARSE_ERROR, "multidimensional arrays for structures are not supported");

			break;
		case ECPGt_varchar:
		case ECPGt_bytea:
			/* pointer has to get dimension 0 */
			if (pointer_len)
				*dimension = mm_strdup("0");

			/* one index is the string length */
			if (atoi(*length) < 0)
			{
				*length = *dimension;
				*dimension = mm_strdup("-1");
			}

			break;
		case ECPGt_char:
		case ECPGt_unsigned_char:
		case ECPGt_string:
			/* char ** */
			if (pointer_len == 2)
			{
				*length = *dimension = mm_strdup("0");
				break;
			}

			/* pointer has to get length 0 */
			if (pointer_len == 1)
				*length = mm_strdup("0");

			/* one index is the string length */
			if (atoi(*length) < 0)
			{
				/*
				 * make sure we return length = -1 for arrays without given
				 * bounds
				 */
				if (atoi(*dimension) < 0 && !type_definition)

					/*
					 * do not change this for typedefs since it will be
					 * changed later on when the variable is defined
					 */
					*length = mm_strdup("1");
				else if (strcmp(*dimension, "0") == 0)
					*length = mm_strdup("-1");
				else
					*length = *dimension;

				*dimension = mm_strdup("-1");
			}
			break;
		default:
			/* a pointer has dimension = 0 */
			if (pointer_len)
			{
				*length = *dimension;
				*dimension = mm_strdup("0");
			}

			if (atoi(*length) >= 0)
				mmfatal(PARSE_ERROR, "multidimensional arrays for simple data types are not supported");

			break;
	}
}