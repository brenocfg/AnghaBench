#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union config_var_val {int /*<<< orphan*/  enumval; int /*<<< orphan*/ * stringval; int /*<<< orphan*/  realval; int /*<<< orphan*/  intval; int /*<<< orphan*/  boolval; } ;
struct TYPE_6__ {int flags; } ;
struct config_string {TYPE_3__ gen; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct config_real {int /*<<< orphan*/  max; int /*<<< orphan*/  min; TYPE_2__ gen; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct config_int {int /*<<< orphan*/  max; int /*<<< orphan*/  min; TYPE_1__ gen; } ;
struct config_generic {int vartype; } ;
struct config_enum {int dummy; } ;
struct config_bool {int dummy; } ;
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int GUC_IS_NAME ; 
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 
 int /*<<< orphan*/  _ (char const*) ; 
 int /*<<< orphan*/  call_bool_check_hook (struct config_bool*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_enum_check_hook (struct config_enum*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_int_check_hook (struct config_int*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_real_check_hook (struct config_real*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_string_check_hook (struct config_string*,int /*<<< orphan*/ **,void**,int /*<<< orphan*/ ,int) ; 
 char* config_enum_get_options (struct config_enum*,char*,char*,char*) ; 
 int /*<<< orphan*/  config_enum_lookup_by_name (struct config_enum*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* get_config_unit_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * guc_strdup (int,char const*) ; 
 int /*<<< orphan*/  parse_bool (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_int (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  parse_real (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
parse_and_validate_value(struct config_generic *record,
						 const char *name, const char *value,
						 GucSource source, int elevel,
						 union config_var_val *newval, void **newextra)
{
	switch (record->vartype)
	{
		case PGC_BOOL:
			{
				struct config_bool *conf = (struct config_bool *) record;

				if (!parse_bool(value, &newval->boolval))
				{
					ereport(elevel,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("parameter \"%s\" requires a Boolean value",
									name)));
					return false;
				}

				if (!call_bool_check_hook(conf, &newval->boolval, newextra,
										  source, elevel))
					return false;
			}
			break;
		case PGC_INT:
			{
				struct config_int *conf = (struct config_int *) record;
				const char *hintmsg;

				if (!parse_int(value, &newval->intval,
							   conf->gen.flags, &hintmsg))
				{
					ereport(elevel,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for parameter \"%s\": \"%s\"",
									name, value),
							 hintmsg ? errhint("%s", _(hintmsg)) : 0));
					return false;
				}

				if (newval->intval < conf->min || newval->intval > conf->max)
				{
					const char *unit = get_config_unit_name(conf->gen.flags);

					ereport(elevel,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("%d%s%s is outside the valid range for parameter \"%s\" (%d .. %d)",
									newval->intval,
									unit ? " " : "",
									unit ? unit : "",
									name,
									conf->min, conf->max)));
					return false;
				}

				if (!call_int_check_hook(conf, &newval->intval, newextra,
										 source, elevel))
					return false;
			}
			break;
		case PGC_REAL:
			{
				struct config_real *conf = (struct config_real *) record;
				const char *hintmsg;

				if (!parse_real(value, &newval->realval,
								conf->gen.flags, &hintmsg))
				{
					ereport(elevel,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for parameter \"%s\": \"%s\"",
									name, value),
							 hintmsg ? errhint("%s", _(hintmsg)) : 0));
					return false;
				}

				if (newval->realval < conf->min || newval->realval > conf->max)
				{
					const char *unit = get_config_unit_name(conf->gen.flags);

					ereport(elevel,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("%g%s%s is outside the valid range for parameter \"%s\" (%g .. %g)",
									newval->realval,
									unit ? " " : "",
									unit ? unit : "",
									name,
									conf->min, conf->max)));
					return false;
				}

				if (!call_real_check_hook(conf, &newval->realval, newextra,
										  source, elevel))
					return false;
			}
			break;
		case PGC_STRING:
			{
				struct config_string *conf = (struct config_string *) record;

				/*
				 * The value passed by the caller could be transient, so we
				 * always strdup it.
				 */
				newval->stringval = guc_strdup(elevel, value);
				if (newval->stringval == NULL)
					return false;

				/*
				 * The only built-in "parsing" check we have is to apply
				 * truncation if GUC_IS_NAME.
				 */
				if (conf->gen.flags & GUC_IS_NAME)
					truncate_identifier(newval->stringval,
										strlen(newval->stringval),
										true);

				if (!call_string_check_hook(conf, &newval->stringval, newextra,
											source, elevel))
				{
					free(newval->stringval);
					newval->stringval = NULL;
					return false;
				}
			}
			break;
		case PGC_ENUM:
			{
				struct config_enum *conf = (struct config_enum *) record;

				if (!config_enum_lookup_by_name(conf, value, &newval->enumval))
				{
					char	   *hintmsg;

					hintmsg = config_enum_get_options(conf,
													  "Available values: ",
													  ".", ", ");

					ereport(elevel,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid value for parameter \"%s\": \"%s\"",
									name, value),
							 hintmsg ? errhint("%s", _(hintmsg)) : 0));

					if (hintmsg)
						pfree(hintmsg);
					return false;
				}

				if (!call_enum_check_hook(conf, &newval->enumval, newextra,
										  source, elevel))
					return false;
			}
			break;
	}

	return true;
}