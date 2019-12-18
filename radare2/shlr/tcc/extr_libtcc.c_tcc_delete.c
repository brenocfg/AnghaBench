#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* runtime_mem; int /*<<< orphan*/  mem_size; struct TYPE_5__* write_mem; struct TYPE_5__* os; struct TYPE_5__* arch; int /*<<< orphan*/  nb_target_deps; int /*<<< orphan*/  target_deps; int /*<<< orphan*/  nb_files; int /*<<< orphan*/  files; struct TYPE_5__* deps_outfile; struct TYPE_5__* outfile; struct TYPE_5__* fini_symbol; struct TYPE_5__* init_symbol; struct TYPE_5__* rpath; struct TYPE_5__* soname; struct TYPE_5__* tcc_lib_path; int /*<<< orphan*/  nb_sysinclude_paths; int /*<<< orphan*/  sysinclude_paths; int /*<<< orphan*/  nb_include_paths; int /*<<< orphan*/  include_paths; int /*<<< orphan*/  nb_cached_includes; int /*<<< orphan*/  cached_includes; int /*<<< orphan*/  nb_crt_paths; int /*<<< orphan*/  crt_paths; int /*<<< orphan*/  nb_library_paths; int /*<<< orphan*/  library_paths; } ;
typedef  TYPE_1__ TCCState ;

/* Variables and functions */
 int /*<<< orphan*/  dynarray_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  munmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcc_cleanup () ; 

void tcc_delete(TCCState *s1)
{
	tcc_cleanup ();

	/* free library paths */
	dynarray_reset (&s1->library_paths, &s1->nb_library_paths);
	dynarray_reset (&s1->crt_paths, &s1->nb_crt_paths);

	/* free include paths */
	dynarray_reset (&s1->cached_includes, &s1->nb_cached_includes);
	dynarray_reset (&s1->include_paths, &s1->nb_include_paths);
	dynarray_reset (&s1->sysinclude_paths, &s1->nb_sysinclude_paths);

	free (s1->tcc_lib_path);
	free (s1->soname);
	free (s1->rpath);
	free (s1->init_symbol);
	free (s1->fini_symbol);
	free (s1->outfile);
	free (s1->deps_outfile);
	dynarray_reset (&s1->files, &s1->nb_files);
	dynarray_reset (&s1->target_deps, &s1->nb_target_deps);

	/* target config */
	free (s1->arch);
	free (s1->os);

#ifdef TCC_IS_NATIVE
#ifdef HAVE_SELINUX
	munmap (s1->write_mem, s1->mem_size);
	munmap (s1->runtime_mem, s1->mem_size);
#else
	free (s1->runtime_mem);
#endif
#endif

	free (s1);
}