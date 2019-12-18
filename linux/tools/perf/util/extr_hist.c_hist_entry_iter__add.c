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
struct map {int dummy; } ;
struct hist_entry_iter {int (* add_entry_cb ) (struct hist_entry_iter*,struct addr_location*,int,void*) ;TYPE_1__* ops; scalar_t__ he; int /*<<< orphan*/  evsel; int /*<<< orphan*/  parent; int /*<<< orphan*/  sample; } ;
struct addr_location {int /*<<< orphan*/  map; } ;
struct TYPE_2__ {int (* prepare_entry ) (struct hist_entry_iter*,struct addr_location*) ;int (* add_single_entry ) (struct hist_entry_iter*,struct addr_location*) ;int (* add_next_entry ) (struct hist_entry_iter*,struct addr_location*) ;int (* finish_entry ) (struct hist_entry_iter*,struct addr_location*) ;scalar_t__ (* next_entry ) (struct hist_entry_iter*,struct addr_location*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  callchain_cursor ; 
 struct map* map__get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__put (struct map*) ; 
 int sample__resolve_callchain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct addr_location*,int) ; 
 int stub1 (struct hist_entry_iter*,struct addr_location*) ; 
 int stub2 (struct hist_entry_iter*,struct addr_location*) ; 
 int stub3 (struct hist_entry_iter*,struct addr_location*,int,void*) ; 
 scalar_t__ stub4 (struct hist_entry_iter*,struct addr_location*) ; 
 int stub5 (struct hist_entry_iter*,struct addr_location*) ; 
 int stub6 (struct hist_entry_iter*,struct addr_location*,int,void*) ; 
 int stub7 (struct hist_entry_iter*,struct addr_location*) ; 

int hist_entry_iter__add(struct hist_entry_iter *iter, struct addr_location *al,
			 int max_stack_depth, void *arg)
{
	int err, err2;
	struct map *alm = NULL;

	if (al)
		alm = map__get(al->map);

	err = sample__resolve_callchain(iter->sample, &callchain_cursor, &iter->parent,
					iter->evsel, al, max_stack_depth);
	if (err) {
		map__put(alm);
		return err;
	}

	err = iter->ops->prepare_entry(iter, al);
	if (err)
		goto out;

	err = iter->ops->add_single_entry(iter, al);
	if (err)
		goto out;

	if (iter->he && iter->add_entry_cb) {
		err = iter->add_entry_cb(iter, al, true, arg);
		if (err)
			goto out;
	}

	while (iter->ops->next_entry(iter, al)) {
		err = iter->ops->add_next_entry(iter, al);
		if (err)
			break;

		if (iter->he && iter->add_entry_cb) {
			err = iter->add_entry_cb(iter, al, false, arg);
			if (err)
				goto out;
		}
	}

out:
	err2 = iter->ops->finish_entry(iter, al);
	if (!err)
		err = err2;

	map__put(alm);

	return err;
}