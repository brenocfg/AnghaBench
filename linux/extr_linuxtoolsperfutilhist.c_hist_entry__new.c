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
struct hist_entry_ops {int /*<<< orphan*/  (* free ) (struct hist_entry*) ;struct hist_entry* (* new ) (size_t) ;} ;
struct hist_entry {struct hist_entry_ops* ops; } ;
struct callchain_root {int dummy; } ;
struct TYPE_2__ {scalar_t__ use_callchain; } ;

/* Variables and functions */
 struct hist_entry_ops default_ops ; 
 int hist_entry__init (struct hist_entry*,struct hist_entry*,int,size_t) ; 
 struct hist_entry* stub1 (size_t) ; 
 int /*<<< orphan*/  stub2 (struct hist_entry*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static struct hist_entry *hist_entry__new(struct hist_entry *template,
					  bool sample_self)
{
	struct hist_entry_ops *ops = template->ops;
	size_t callchain_size = 0;
	struct hist_entry *he;
	int err = 0;

	if (!ops)
		ops = template->ops = &default_ops;

	if (symbol_conf.use_callchain)
		callchain_size = sizeof(struct callchain_root);

	he = ops->new(callchain_size);
	if (he) {
		err = hist_entry__init(he, template, sample_self, callchain_size);
		if (err) {
			ops->free(he);
			he = NULL;
		}
	}

	return he;
}