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
struct dso {int short_name_allocated; int long_name_allocated; char* symsrc_filename; int /*<<< orphan*/  lock; int /*<<< orphan*/  nsinfo; int /*<<< orphan*/  auxtrace_cache; int /*<<< orphan*/  long_name; int /*<<< orphan*/  short_name; int /*<<< orphan*/  symbols; int /*<<< orphan*/  srclines; int /*<<< orphan*/  inlined_nodes; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auxtrace_cache__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__data_close (struct dso*) ; 
 int /*<<< orphan*/  dso__free_a2l (struct dso*) ; 
 int /*<<< orphan*/  dso_cache__free (struct dso*) ; 
 int /*<<< orphan*/  free (struct dso*) ; 
 int /*<<< orphan*/  inlines__tree_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsinfo__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcline__tree_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbols__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (char**) ; 

void dso__delete(struct dso *dso)
{
	if (!RB_EMPTY_NODE(&dso->rb_node))
		pr_err("DSO %s is still in rbtree when being deleted!\n",
		       dso->long_name);

	/* free inlines first, as they reference symbols */
	inlines__tree_delete(&dso->inlined_nodes);
	srcline__tree_delete(&dso->srclines);
	symbols__delete(&dso->symbols);

	if (dso->short_name_allocated) {
		zfree((char **)&dso->short_name);
		dso->short_name_allocated = false;
	}

	if (dso->long_name_allocated) {
		zfree((char **)&dso->long_name);
		dso->long_name_allocated = false;
	}

	dso__data_close(dso);
	auxtrace_cache__free(dso->auxtrace_cache);
	dso_cache__free(dso);
	dso__free_a2l(dso);
	zfree(&dso->symsrc_filename);
	nsinfo__zput(dso->nsinfo);
	pthread_mutex_destroy(&dso->lock);
	free(dso);
}