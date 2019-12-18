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
struct TYPE_2__ {int fd; int /*<<< orphan*/  open_entry; int /*<<< orphan*/  status; int /*<<< orphan*/  cache; } ;
struct dso {int is_64_bit; int has_srcline; int a2l_fails; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; TYPE_1__ data; int /*<<< orphan*/  node; int /*<<< orphan*/ * root; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  comp; int /*<<< orphan*/  needs_swap; int /*<<< orphan*/  kernel; scalar_t__ has_build_id; scalar_t__ sorted_by_name; scalar_t__ rel; scalar_t__ loaded; void* binary_type; void* symtab_type; void* srclines; void* inlined_nodes; void* symbol_names; void* symbols; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ID__NONE ; 
 void* DSO_BINARY_TYPE__NOT_FOUND ; 
 int /*<<< orphan*/  DSO_DATA_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  DSO_SWAP__UNSET ; 
 int /*<<< orphan*/  DSO_TYPE_USER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 void* RB_ROOT_CACHED ; 
 struct dso* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dso__set_short_name (struct dso*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct dso *dso__new(const char *name)
{
	struct dso *dso = calloc(1, sizeof(*dso) + strlen(name) + 1);

	if (dso != NULL) {
		strcpy(dso->name, name);
		dso__set_long_name(dso, dso->name, false);
		dso__set_short_name(dso, dso->name, false);
		dso->symbols = dso->symbol_names = RB_ROOT_CACHED;
		dso->data.cache = RB_ROOT;
		dso->inlined_nodes = RB_ROOT_CACHED;
		dso->srclines = RB_ROOT_CACHED;
		dso->data.fd = -1;
		dso->data.status = DSO_DATA_STATUS_UNKNOWN;
		dso->symtab_type = DSO_BINARY_TYPE__NOT_FOUND;
		dso->binary_type = DSO_BINARY_TYPE__NOT_FOUND;
		dso->is_64_bit = (sizeof(void *) == 8);
		dso->loaded = 0;
		dso->rel = 0;
		dso->sorted_by_name = 0;
		dso->has_build_id = 0;
		dso->has_srcline = 1;
		dso->a2l_fails = 1;
		dso->kernel = DSO_TYPE_USER;
		dso->needs_swap = DSO_SWAP__UNSET;
		dso->comp = COMP_ID__NONE;
		RB_CLEAR_NODE(&dso->rb_node);
		dso->root = NULL;
		INIT_LIST_HEAD(&dso->node);
		INIT_LIST_HEAD(&dso->data.open_entry);
		pthread_mutex_init(&dso->lock, NULL);
		refcount_set(&dso->refcnt, 1);
	}

	return dso;
}