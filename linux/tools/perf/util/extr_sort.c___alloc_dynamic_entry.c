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
struct tep_format_field {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int elide; int level; scalar_t__ user_len; scalar_t__ len; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  list; int /*<<< orphan*/  free; int /*<<< orphan*/  equal; void* sort; void* collapse; void* cmp; int /*<<< orphan*/ * color; int /*<<< orphan*/  entry; int /*<<< orphan*/  width; int /*<<< orphan*/  header; int /*<<< orphan*/  name; } ;
struct hpp_dynamic_entry {TYPE_1__ hpp; scalar_t__ dynamic_len; struct tep_format_field* field; struct evsel* evsel; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* __sort__hde_cmp ; 
 int /*<<< orphan*/  __sort__hde_entry ; 
 int /*<<< orphan*/  __sort__hde_equal ; 
 int /*<<< orphan*/  __sort__hde_header ; 
 int /*<<< orphan*/  __sort__hde_width ; 
 int /*<<< orphan*/  hde_free ; 
 struct hpp_dynamic_entry* malloc (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static struct hpp_dynamic_entry *
__alloc_dynamic_entry(struct evsel *evsel, struct tep_format_field *field,
		      int level)
{
	struct hpp_dynamic_entry *hde;

	hde = malloc(sizeof(*hde));
	if (hde == NULL) {
		pr_debug("Memory allocation failed\n");
		return NULL;
	}

	hde->evsel = evsel;
	hde->field = field;
	hde->dynamic_len = 0;

	hde->hpp.name = field->name;
	hde->hpp.header = __sort__hde_header;
	hde->hpp.width  = __sort__hde_width;
	hde->hpp.entry  = __sort__hde_entry;
	hde->hpp.color  = NULL;

	hde->hpp.cmp = __sort__hde_cmp;
	hde->hpp.collapse = __sort__hde_cmp;
	hde->hpp.sort = __sort__hde_cmp;
	hde->hpp.equal = __sort__hde_equal;
	hde->hpp.free = hde_free;

	INIT_LIST_HEAD(&hde->hpp.list);
	INIT_LIST_HEAD(&hde->hpp.sort_list);
	hde->hpp.elide = false;
	hde->hpp.len = 0;
	hde->hpp.user_len = 0;
	hde->hpp.level = level;

	return hde;
}