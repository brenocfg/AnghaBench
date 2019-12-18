#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct variable {int const brace_level; TYPE_1__* type; } ;
struct TYPE_4__ {struct ECPGtype* element; } ;
struct ECPGtype {int type; char* type_name; char* size; int /*<<< orphan*/  counter; TYPE_2__ u; } ;
struct TYPE_3__ {int type; char* type_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGdump_a_simple (int /*<<< orphan*/ *,char const*,scalar_t__,char*,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGdump_a_struct (int /*<<< orphan*/ *,char const*,char const*,char*,struct ECPGtype*,struct ECPGtype*,char const*,char const*) ; 
 scalar_t__ ECPGt_NO_INDICATOR ; 
#define  ECPGt_array 132 
#define  ECPGt_char_variable 131 
 int ECPGt_const ; 
#define  ECPGt_descriptor 130 
 int ECPGt_sqlda ; 
#define  ECPGt_struct 129 
#define  ECPGt_union 128 
 int /*<<< orphan*/  ET_ERROR ; 
 int /*<<< orphan*/  ET_WARNING ; 
 int /*<<< orphan*/  INDICATOR_NOT_ARRAY ; 
 int /*<<< orphan*/  INDICATOR_NOT_SIMPLE ; 
 int /*<<< orphan*/  INDICATOR_NOT_STRUCT ; 
 int /*<<< orphan*/  IS_SIMPLE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  base_yyerror (char*) ; 
 struct variable* find_variable (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  indicator_set ; 
 char* mm_strdup (char const*) ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
ECPGdump_a_type(FILE *o, const char *name, struct ECPGtype *type, const int brace_level,
				const char *ind_name, struct ECPGtype *ind_type, const int ind_brace_level,
				const char *prefix, const char *ind_prefix,
				char *arr_str_size, const char *struct_sizeof,
				const char *ind_struct_sizeof)
{
	struct variable *var;

	if (type->type != ECPGt_descriptor && type->type != ECPGt_sqlda &&
		type->type != ECPGt_char_variable && type->type != ECPGt_const &&
		brace_level >= 0)
	{
		char	   *str;

		str = mm_strdup(name);
		var = find_variable(str);
		free(str);

		if ((var->type->type != type->type) ||
			(var->type->type_name && !type->type_name) ||
			(!var->type->type_name && type->type_name) ||
			(var->type->type_name && type->type_name && strcmp(var->type->type_name, type->type_name) != 0))
			mmerror(PARSE_ERROR, ET_ERROR, "variable \"%s\" is hidden by a local variable of a different type", name);
		else if (var->brace_level != brace_level)
			mmerror(PARSE_ERROR, ET_WARNING, "variable \"%s\" is hidden by a local variable", name);

		if (ind_name && ind_type && ind_type->type != ECPGt_NO_INDICATOR && ind_brace_level >= 0)
		{
			str = mm_strdup(ind_name);
			var = find_variable(str);
			free(str);

			if ((var->type->type != ind_type->type) ||
				(var->type->type_name && !ind_type->type_name) ||
				(!var->type->type_name && ind_type->type_name) ||
				(var->type->type_name && ind_type->type_name && strcmp(var->type->type_name, ind_type->type_name) != 0))
				mmerror(PARSE_ERROR, ET_ERROR, "indicator variable \"%s\" is hidden by a local variable of a different type", ind_name);
			else if (var->brace_level != ind_brace_level)
				mmerror(PARSE_ERROR, ET_WARNING, "indicator variable \"%s\" is hidden by a local variable", ind_name);
		}
	}

	switch (type->type)
	{
		case ECPGt_array:
			if (indicator_set && ind_type->type != ECPGt_array)
				mmfatal(INDICATOR_NOT_ARRAY, "indicator for array/pointer has to be array/pointer");
			switch (type->u.element->type)
			{
				case ECPGt_array:
					mmerror(PARSE_ERROR, ET_ERROR, "nested arrays are not supported (except strings)"); /* array of array */
					break;
				case ECPGt_struct:
				case ECPGt_union:
					ECPGdump_a_struct(o, name,
									  ind_name,
									  type->size,
									  type->u.element,
									  (ind_type == NULL) ? NULL : ((ind_type->type == ECPGt_NO_INDICATOR) ? ind_type : ind_type->u.element),
									  prefix, ind_prefix);
					break;
				default:
					if (!IS_SIMPLE_TYPE(type->u.element->type))
						base_yyerror("internal error: unknown datatype, please report this to <pgsql-bugs@lists.postgresql.org>");

					ECPGdump_a_simple(o, name,
									  type->u.element->type,
									  type->u.element->size, type->size, struct_sizeof ? struct_sizeof : NULL,
									  prefix, type->u.element->counter);

					if (ind_type != NULL)
					{
						if (ind_type->type == ECPGt_NO_INDICATOR)
						{
							char	   *str_neg_one = mm_strdup("-1");

							ECPGdump_a_simple(o, ind_name, ind_type->type, ind_type->size, str_neg_one, NULL, ind_prefix, 0);
							free(str_neg_one);
						}
						else
						{
							ECPGdump_a_simple(o, ind_name, ind_type->u.element->type,
											  ind_type->u.element->size, ind_type->size, NULL, ind_prefix, 0);
						}
					}
			}
			break;
		case ECPGt_struct:
			{
				char	   *str_one = mm_strdup("1");

				if (indicator_set && ind_type->type != ECPGt_struct)
					mmfatal(INDICATOR_NOT_STRUCT, "indicator for struct has to be a struct");

				ECPGdump_a_struct(o, name, ind_name, str_one, type, ind_type, prefix, ind_prefix);
				free(str_one);
			}
			break;
		case ECPGt_union:		/* cannot dump a complete union */
			base_yyerror("type of union has to be specified");
			break;
		case ECPGt_char_variable:
			{
				/*
				 * Allocate for each, as there are code-paths where the values
				 * get stomped on.
				 */
				char	   *str_varchar_one = mm_strdup("1");
				char	   *str_arr_one = mm_strdup("1");
				char	   *str_neg_one = mm_strdup("-1");

				if (indicator_set && (ind_type->type == ECPGt_struct || ind_type->type == ECPGt_array))
					mmfatal(INDICATOR_NOT_SIMPLE, "indicator for simple data type has to be simple");

				ECPGdump_a_simple(o, name, type->type, str_varchar_one, (arr_str_size && strcmp(arr_str_size, "0") != 0) ? arr_str_size : str_arr_one, struct_sizeof, prefix, 0);
				if (ind_type != NULL)
					ECPGdump_a_simple(o, ind_name, ind_type->type, ind_type->size, (arr_str_size && strcmp(arr_str_size, "0") != 0) ? arr_str_size : str_neg_one, ind_struct_sizeof, ind_prefix, 0);

				free(str_varchar_one);
				free(str_arr_one);
				free(str_neg_one);
			}
			break;
		case ECPGt_descriptor:
			{
				/*
				 * Allocate for each, as there are code-paths where the values
				 * get stomped on.
				 */
				char	   *str_neg_one = mm_strdup("-1");
				char	   *ind_type_neg_one = mm_strdup("-1");

				if (indicator_set && (ind_type->type == ECPGt_struct || ind_type->type == ECPGt_array))
					mmfatal(INDICATOR_NOT_SIMPLE, "indicator for simple data type has to be simple");

				ECPGdump_a_simple(o, name, type->type, NULL, str_neg_one, NULL, prefix, 0);
				if (ind_type != NULL)
					ECPGdump_a_simple(o, ind_name, ind_type->type, ind_type->size, ind_type_neg_one, NULL, ind_prefix, 0);

				free(str_neg_one);
				free(ind_type_neg_one);
			}
			break;
		default:
			{
				/*
				 * Allocate for each, as there are code-paths where the values
				 * get stomped on.
				 */
				char	   *str_neg_one = mm_strdup("-1");
				char	   *ind_type_neg_one = mm_strdup("-1");

				if (indicator_set && (ind_type->type == ECPGt_struct || ind_type->type == ECPGt_array))
					mmfatal(INDICATOR_NOT_SIMPLE, "indicator for simple data type has to be simple");

				ECPGdump_a_simple(o, name, type->type, type->size, (arr_str_size && strcmp(arr_str_size, "0") != 0) ? arr_str_size : str_neg_one, struct_sizeof, prefix, type->counter);
				if (ind_type != NULL)
					ECPGdump_a_simple(o, ind_name, ind_type->type, ind_type->size, (arr_str_size && strcmp(arr_str_size, "0") != 0) ? arr_str_size : ind_type_neg_one, ind_struct_sizeof, ind_prefix, 0);

				free(str_neg_one);
				free(ind_type_neg_one);
			}
			break;
	}
}