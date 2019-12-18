#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16 ;
typedef  int /*<<< orphan*/  security_context_t ;
typedef  int /*<<< orphan*/  security_class_t ;
struct TYPE_2__ {char* class_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 size_t SEPG_CLASS_MAX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  freecon (int /*<<< orphan*/ ) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 scalar_t__ security_compute_create_name_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* selinux_catalog ; 
 int /*<<< orphan*/  string_to_security_class (char const*) ; 

char *
sepgsql_compute_create(const char *scontext,
					   const char *tcontext,
					   uint16 tclass,
					   const char *objname)
{
	security_context_t ncontext;
	security_class_t tclass_ex;
	const char *tclass_name;
	char	   *result;

	/* Get external code of the object class */
	Assert(tclass < SEPG_CLASS_MAX);

	tclass_name = selinux_catalog[tclass].class_name;
	tclass_ex = string_to_security_class(tclass_name);

	/*
	 * Ask SELinux what is the default context for the given object class on a
	 * pair of security contexts
	 */
	if (security_compute_create_name_raw((security_context_t) scontext,
										 (security_context_t) tcontext,
										 tclass_ex,
										 objname,
										 &ncontext) < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("SELinux could not compute a new context: "
						"scontext=%s tcontext=%s tclass=%s: %m",
						scontext, tcontext, tclass_name)));

	/*
	 * libselinux returns malloc()'ed string, so we need to copy it on the
	 * palloc()'ed region.
	 */
	PG_TRY();
	{
		result = pstrdup(ncontext);
	}
	PG_FINALLY();
	{
		freecon(ncontext);
	}
	PG_END_TRY();

	return result;
}