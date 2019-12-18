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
struct config_generic {char const* short_desc; char const* long_desc; int flags; int vartype; int /*<<< orphan*/  group; scalar_t__ context; int /*<<< orphan*/  name; } ;
typedef  enum config_type { ____Placeholder_config_type } config_type ;
typedef  scalar_t__ GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  CUSTOM_OPTIONS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int GUC_LIST_QUOTE ; 
 scalar_t__ PGC_POSTMASTER ; 
 scalar_t__ PGC_SUSET ; 
 scalar_t__ PGC_USERSET ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ guc_malloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  guc_strdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memset (struct config_generic*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  process_shared_preload_libraries_in_progress ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct config_generic *
init_custom_variable(const char *name,
					 const char *short_desc,
					 const char *long_desc,
					 GucContext context,
					 int flags,
					 enum config_type type,
					 size_t sz)
{
	struct config_generic *gen;

	/*
	 * Only allow custom PGC_POSTMASTER variables to be created during shared
	 * library preload; any later than that, we can't ensure that the value
	 * doesn't change after startup.  This is a fatal elog if it happens; just
	 * erroring out isn't safe because we don't know what the calling loadable
	 * module might already have hooked into.
	 */
	if (context == PGC_POSTMASTER &&
		!process_shared_preload_libraries_in_progress)
		elog(FATAL, "cannot create PGC_POSTMASTER variables after startup");

	/*
	 * We can't support custom GUC_LIST_QUOTE variables, because the wrong
	 * things would happen if such a variable were set or pg_dump'd when the
	 * defining extension isn't loaded.  Again, treat this as fatal because
	 * the loadable module may be partly initialized already.
	 */
	if (flags & GUC_LIST_QUOTE)
		elog(FATAL, "extensions cannot define GUC_LIST_QUOTE variables");

	/*
	 * Before pljava commit 398f3b876ed402bdaec8bc804f29e2be95c75139
	 * (2015-12-15), two of that module's PGC_USERSET variables facilitated
	 * trivial escalation to superuser privileges.  Restrict the variables to
	 * protect sites that have yet to upgrade pljava.
	 */
	if (context == PGC_USERSET &&
		(strcmp(name, "pljava.classpath") == 0 ||
		 strcmp(name, "pljava.vmoptions") == 0))
		context = PGC_SUSET;

	gen = (struct config_generic *) guc_malloc(ERROR, sz);
	memset(gen, 0, sz);

	gen->name = guc_strdup(ERROR, name);
	gen->context = context;
	gen->group = CUSTOM_OPTIONS;
	gen->short_desc = short_desc;
	gen->long_desc = long_desc;
	gen->flags = flags;
	gen->vartype = type;

	return gen;
}