#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_7__ {char* svalue; char* name; TYPE_2__ value; } ;
typedef  TYPE_1__ Variable ;

/* Variables and functions */
 scalar_t__ PGBT_NO_VALUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ is_an_int (char*) ; 
 scalar_t__ pg_strcasecmp (char*,char*) ; 
 scalar_t__ pg_strncasecmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  setBoolValue (TYPE_2__*,int) ; 
 int /*<<< orphan*/  setDoubleValue (TYPE_2__*,double) ; 
 int /*<<< orphan*/  setIntValue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setNullValue (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strtodouble (char*,int,double*) ; 
 int /*<<< orphan*/  strtoint64 (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
makeVariableValue(Variable *var)
{
	size_t		slen;

	if (var->value.type != PGBT_NO_VALUE)
		return true;			/* no work */

	slen = strlen(var->svalue);

	if (slen == 0)
		/* what should it do on ""? */
		return false;

	if (pg_strcasecmp(var->svalue, "null") == 0)
	{
		setNullValue(&var->value);
	}

	/*
	 * accept prefixes such as y, ye, n, no... but not for "o". 0/1 are
	 * recognized later as an int, which is converted to bool if needed.
	 */
	else if (pg_strncasecmp(var->svalue, "true", slen) == 0 ||
			 pg_strncasecmp(var->svalue, "yes", slen) == 0 ||
			 pg_strcasecmp(var->svalue, "on") == 0)
	{
		setBoolValue(&var->value, true);
	}
	else if (pg_strncasecmp(var->svalue, "false", slen) == 0 ||
			 pg_strncasecmp(var->svalue, "no", slen) == 0 ||
			 pg_strcasecmp(var->svalue, "off") == 0 ||
			 pg_strcasecmp(var->svalue, "of") == 0)
	{
		setBoolValue(&var->value, false);
	}
	else if (is_an_int(var->svalue))
	{
		/* if it looks like an int, it must be an int without overflow */
		int64		iv;

		if (!strtoint64(var->svalue, false, &iv))
			return false;

		setIntValue(&var->value, iv);
	}
	else						/* type should be double */
	{
		double		dv;

		if (!strtodouble(var->svalue, true, &dv))
		{
			fprintf(stderr,
					"malformed variable \"%s\" value: \"%s\"\n",
					var->name, var->svalue);
			return false;
		}
		setDoubleValue(&var->value, dv);
	}
	return true;
}