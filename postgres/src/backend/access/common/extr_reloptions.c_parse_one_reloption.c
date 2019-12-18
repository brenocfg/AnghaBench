#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* string_val; int /*<<< orphan*/  enum_val; int /*<<< orphan*/  real_val; int /*<<< orphan*/  int_val; int /*<<< orphan*/  bool_val; } ;
struct TYPE_12__ {int isset; TYPE_2__* gen; TYPE_1__ values; } ;
typedef  TYPE_3__ relopt_value ;
struct TYPE_13__ {int /*<<< orphan*/  (* validate_cb ) (char*) ;} ;
typedef  TYPE_4__ relopt_string ;
struct TYPE_14__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_5__ relopt_real ;
struct TYPE_15__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_6__ relopt_int ;
struct TYPE_16__ {int /*<<< orphan*/  symbol_val; int /*<<< orphan*/  string_val; } ;
typedef  TYPE_7__ relopt_enum_elt_def ;
struct TYPE_17__ {int /*<<< orphan*/  default_val; int /*<<< orphan*/  detailmsg; TYPE_7__* members; } ;
typedef  TYPE_8__ relopt_enum ;
struct TYPE_11__ {char* name; int namelen; int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
#define  RELOPT_TYPE_BOOL 132 
#define  RELOPT_TYPE_ENUM 131 
#define  RELOPT_TYPE_INT 130 
#define  RELOPT_TYPE_REAL 129 
#define  RELOPT_TYPE_STRING 128 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc (int) ; 
 int parse_bool (char*,int /*<<< orphan*/ *) ; 
 int parse_int (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_real (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static void
parse_one_reloption(relopt_value *option, char *text_str, int text_len,
					bool validate)
{
	char	   *value;
	int			value_len;
	bool		parsed;
	bool		nofree = false;

	if (option->isset && validate)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("parameter \"%s\" specified more than once",
						option->gen->name)));

	value_len = text_len - option->gen->namelen - 1;
	value = (char *) palloc(value_len + 1);
	memcpy(value, text_str + option->gen->namelen + 1, value_len);
	value[value_len] = '\0';

	switch (option->gen->type)
	{
		case RELOPT_TYPE_BOOL:
			{
				parsed = parse_bool(value, &option->values.bool_val);
				if (validate && !parsed)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for boolean option \"%s\": %s",
									option->gen->name, value)));
			}
			break;
		case RELOPT_TYPE_INT:
			{
				relopt_int *optint = (relopt_int *) option->gen;

				parsed = parse_int(value, &option->values.int_val, 0, NULL);
				if (validate && !parsed)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for integer option \"%s\": %s",
									option->gen->name, value)));
				if (validate && (option->values.int_val < optint->min ||
								 option->values.int_val > optint->max))
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("value %s out of bounds for option \"%s\"",
									value, option->gen->name),
							 errdetail("Valid values are between \"%d\" and \"%d\".",
									   optint->min, optint->max)));
			}
			break;
		case RELOPT_TYPE_REAL:
			{
				relopt_real *optreal = (relopt_real *) option->gen;

				parsed = parse_real(value, &option->values.real_val, 0, NULL);
				if (validate && !parsed)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for floating point option \"%s\": %s",
									option->gen->name, value)));
				if (validate && (option->values.real_val < optreal->min ||
								 option->values.real_val > optreal->max))
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("value %s out of bounds for option \"%s\"",
									value, option->gen->name),
							 errdetail("Valid values are between \"%f\" and \"%f\".",
									   optreal->min, optreal->max)));
			}
			break;
		case RELOPT_TYPE_ENUM:
			{
				relopt_enum *optenum = (relopt_enum *) option->gen;
				relopt_enum_elt_def *elt;

				parsed = false;
				for (elt = optenum->members; elt->string_val; elt++)
				{
					if (pg_strcasecmp(value, elt->string_val) == 0)
					{
						option->values.enum_val = elt->symbol_val;
						parsed = true;
						break;
					}
				}
				if (validate && !parsed)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for enum option \"%s\": %s",
									option->gen->name, value),
							 optenum->detailmsg ?
							 errdetail_internal("%s", _(optenum->detailmsg)) : 0));

				/*
				 * If value is not among the allowed string values, but we are
				 * not asked to validate, just use the default numeric value.
				 */
				if (!parsed)
					option->values.enum_val = optenum->default_val;
			}
			break;
		case RELOPT_TYPE_STRING:
			{
				relopt_string *optstring = (relopt_string *) option->gen;

				option->values.string_val = value;
				nofree = true;
				if (validate && optstring->validate_cb)
					(optstring->validate_cb) (value);
				parsed = true;
			}
			break;
		default:
			elog(ERROR, "unsupported reloption type %d", option->gen->type);
			parsed = true;		/* quiet compiler */
			break;
	}

	if (parsed)
		option->isset = true;
	if (!nofree)
		pfree(value);
}