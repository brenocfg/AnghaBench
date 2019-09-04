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
struct sort_dimension {TYPE_1__* entry; } ;
struct TYPE_4__ {int elide; int level; scalar_t__ user_len; scalar_t__ len; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  list; int /*<<< orphan*/  free; int /*<<< orphan*/  equal; int /*<<< orphan*/  sort; int /*<<< orphan*/  collapse; int /*<<< orphan*/  cmp; int /*<<< orphan*/ * color; int /*<<< orphan*/  entry; int /*<<< orphan*/  width; int /*<<< orphan*/  header; int /*<<< orphan*/  name; } ;
struct hpp_sort_entry {TYPE_2__ hpp; TYPE_1__* se; } ;
struct TYPE_3__ {int /*<<< orphan*/  se_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sort__hpp_cmp ; 
 int /*<<< orphan*/  __sort__hpp_collapse ; 
 int /*<<< orphan*/  __sort__hpp_entry ; 
 int /*<<< orphan*/  __sort__hpp_equal ; 
 int /*<<< orphan*/  __sort__hpp_header ; 
 int /*<<< orphan*/  __sort__hpp_sort ; 
 int /*<<< orphan*/  __sort__hpp_width ; 
 int /*<<< orphan*/  hse_free ; 
 struct hpp_sort_entry* malloc (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct hpp_sort_entry *
__sort_dimension__alloc_hpp(struct sort_dimension *sd, int level)
{
	struct hpp_sort_entry *hse;

	hse = malloc(sizeof(*hse));
	if (hse == NULL) {
		pr_err("Memory allocation failed\n");
		return NULL;
	}

	hse->se = sd->entry;
	hse->hpp.name = sd->entry->se_header;
	hse->hpp.header = __sort__hpp_header;
	hse->hpp.width = __sort__hpp_width;
	hse->hpp.entry = __sort__hpp_entry;
	hse->hpp.color = NULL;

	hse->hpp.cmp = __sort__hpp_cmp;
	hse->hpp.collapse = __sort__hpp_collapse;
	hse->hpp.sort = __sort__hpp_sort;
	hse->hpp.equal = __sort__hpp_equal;
	hse->hpp.free = hse_free;

	INIT_LIST_HEAD(&hse->hpp.list);
	INIT_LIST_HEAD(&hse->hpp.sort_list);
	hse->hpp.elide = false;
	hse->hpp.len = 0;
	hse->hpp.user_len = 0;
	hse->hpp.level = level;

	return hse;
}