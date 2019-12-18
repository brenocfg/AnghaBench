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
struct config_string {char** variable; } ;
struct config_real {int /*<<< orphan*/ * variable; } ;
struct config_int {char** variable; } ;
struct config_generic {char* name; int vartype; char* sourcefile; int /*<<< orphan*/  scontext; int /*<<< orphan*/  source; int /*<<< orphan*/  sourceline; } ;
struct config_enum {int /*<<< orphan*/ * variable; } ;
struct config_bool {int /*<<< orphan*/ * variable; } ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 
 int /*<<< orphan*/  REALTYPE_PRECISION ; 
 scalar_t__ can_skip_gucvar (struct config_generic*) ; 
 char* config_enum_lookup_by_value (struct config_enum*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_serialize (char**,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  do_serialize_binary (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
serialize_variable(char **destptr, Size *maxbytes,
				   struct config_generic *gconf)
{
	if (can_skip_gucvar(gconf))
		return;

	do_serialize(destptr, maxbytes, "%s", gconf->name);

	switch (gconf->vartype)
	{
		case PGC_BOOL:
			{
				struct config_bool *conf = (struct config_bool *) gconf;

				do_serialize(destptr, maxbytes,
							 (*conf->variable ? "true" : "false"));
			}
			break;

		case PGC_INT:
			{
				struct config_int *conf = (struct config_int *) gconf;

				do_serialize(destptr, maxbytes, "%d", *conf->variable);
			}
			break;

		case PGC_REAL:
			{
				struct config_real *conf = (struct config_real *) gconf;

				do_serialize(destptr, maxbytes, "%.*e",
							 REALTYPE_PRECISION, *conf->variable);
			}
			break;

		case PGC_STRING:
			{
				struct config_string *conf = (struct config_string *) gconf;

				/* NULL becomes empty string, see estimate_variable_size() */
				do_serialize(destptr, maxbytes, "%s",
							 *conf->variable ? *conf->variable : "");
			}
			break;

		case PGC_ENUM:
			{
				struct config_enum *conf = (struct config_enum *) gconf;

				do_serialize(destptr, maxbytes, "%s",
							 config_enum_lookup_by_value(conf, *conf->variable));
			}
			break;
	}

	do_serialize(destptr, maxbytes, "%s",
				 (gconf->sourcefile ? gconf->sourcefile : ""));

	if (gconf->sourcefile && gconf->sourcefile[0])
		do_serialize_binary(destptr, maxbytes, &gconf->sourceline,
							sizeof(gconf->sourceline));

	do_serialize_binary(destptr, maxbytes, &gconf->source,
						sizeof(gconf->source));
	do_serialize_binary(destptr, maxbytes, &gconf->scontext,
						sizeof(gconf->scontext));
}