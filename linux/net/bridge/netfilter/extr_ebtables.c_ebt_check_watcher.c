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
struct xt_tgchk_param {int /*<<< orphan*/  targinfo; struct xt_target* target; struct ebt_entry* entryinfo; } ;
struct xt_target {scalar_t__ family; int /*<<< orphan*/  me; } ;
struct TYPE_2__ {struct xt_target* watcher; int /*<<< orphan*/  name; } ;
struct ebt_entry_watcher {size_t watcher_size; int /*<<< orphan*/  data; TYPE_1__ u; } ;
struct ebt_entry {int target_offset; int invflags; int /*<<< orphan*/  ethproto; } ;

/* Variables and functions */
 int EBT_IPROTO ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct xt_target*) ; 
 scalar_t__ NFPROTO_BRIDGE ; 
 int PTR_ERR (struct xt_target*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int xt_check_target (struct xt_tgchk_param*,size_t,int /*<<< orphan*/ ,int) ; 
 struct xt_target* xt_request_find_target (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ebt_check_watcher(struct ebt_entry_watcher *w, struct xt_tgchk_param *par,
		  unsigned int *cnt)
{
	const struct ebt_entry *e = par->entryinfo;
	struct xt_target *watcher;
	size_t left = ((char *)e + e->target_offset) - (char *)w;
	int ret;

	if (left < sizeof(struct ebt_entry_watcher) ||
	   left - sizeof(struct ebt_entry_watcher) < w->watcher_size)
		return -EINVAL;

	watcher = xt_request_find_target(NFPROTO_BRIDGE, w->u.name, 0);
	if (IS_ERR(watcher))
		return PTR_ERR(watcher);

	if (watcher->family != NFPROTO_BRIDGE) {
		module_put(watcher->me);
		return -ENOENT;
	}

	w->u.watcher = watcher;

	par->target   = watcher;
	par->targinfo = w->data;
	ret = xt_check_target(par, w->watcher_size,
	      ntohs(e->ethproto), e->invflags & EBT_IPROTO);
	if (ret < 0) {
		module_put(watcher->me);
		return ret;
	}

	(*cnt)++;
	return 0;
}