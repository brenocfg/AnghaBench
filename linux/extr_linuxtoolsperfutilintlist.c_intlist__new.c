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
struct TYPE_2__ {int /*<<< orphan*/  node_delete; int /*<<< orphan*/  node_new; int /*<<< orphan*/  node_cmp; } ;
struct intlist {TYPE_1__ rblist; } ;

/* Variables and functions */
 int /*<<< orphan*/  intlist__delete (struct intlist*) ; 
 int /*<<< orphan*/  intlist__node_cmp ; 
 int /*<<< orphan*/  intlist__node_delete ; 
 int /*<<< orphan*/  intlist__node_new ; 
 scalar_t__ intlist__parse_list (struct intlist*,char const*) ; 
 struct intlist* malloc (int) ; 
 int /*<<< orphan*/  rblist__init (TYPE_1__*) ; 

struct intlist *intlist__new(const char *slist)
{
	struct intlist *ilist = malloc(sizeof(*ilist));

	if (ilist != NULL) {
		rblist__init(&ilist->rblist);
		ilist->rblist.node_cmp    = intlist__node_cmp;
		ilist->rblist.node_new    = intlist__node_new;
		ilist->rblist.node_delete = intlist__node_delete;

		if (slist && intlist__parse_list(ilist, slist))
			goto out_delete;
	}

	return ilist;
out_delete:
	intlist__delete(ilist);
	return NULL;
}