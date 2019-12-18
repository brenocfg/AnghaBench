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
typedef  int /*<<< orphan*/  used ;
typedef  int /*<<< orphan*/  u16 ;
struct xt_mtchk_param {size_t family; int hook_mask; TYPE_1__* match; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  allow ;
struct TYPE_2__ {int matchsize; int hooks; int (* checkentry ) (struct xt_mtchk_param*) ;int /*<<< orphan*/  proto; int /*<<< orphan*/  name; int /*<<< orphan*/ * table; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int XT_ALIGN (int) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct xt_mtchk_param*) ; 
 int /*<<< orphan*/  textify_hooks (char*,int,int,size_t) ; 
 int /*<<< orphan*/ * xt_prefix ; 

int xt_check_match(struct xt_mtchk_param *par,
		   unsigned int size, u16 proto, bool inv_proto)
{
	int ret;

	if (XT_ALIGN(par->match->matchsize) != size &&
	    par->match->matchsize != -1) {
		/*
		 * ebt_among is exempt from centralized matchsize checking
		 * because it uses a dynamic-size data set.
		 */
		pr_err_ratelimited("%s_tables: %s.%u match: invalid size %u (kernel) != (user) %u\n",
				   xt_prefix[par->family], par->match->name,
				   par->match->revision,
				   XT_ALIGN(par->match->matchsize), size);
		return -EINVAL;
	}
	if (par->match->table != NULL &&
	    strcmp(par->match->table, par->table) != 0) {
		pr_info_ratelimited("%s_tables: %s match: only valid in %s table, not %s\n",
				    xt_prefix[par->family], par->match->name,
				    par->match->table, par->table);
		return -EINVAL;
	}
	if (par->match->hooks && (par->hook_mask & ~par->match->hooks) != 0) {
		char used[64], allow[64];

		pr_info_ratelimited("%s_tables: %s match: used from hooks %s, but only valid from %s\n",
				    xt_prefix[par->family], par->match->name,
				    textify_hooks(used, sizeof(used),
						  par->hook_mask, par->family),
				    textify_hooks(allow, sizeof(allow),
						  par->match->hooks,
						  par->family));
		return -EINVAL;
	}
	if (par->match->proto && (par->match->proto != proto || inv_proto)) {
		pr_info_ratelimited("%s_tables: %s match: only valid for protocol %u\n",
				    xt_prefix[par->family], par->match->name,
				    par->match->proto);
		return -EINVAL;
	}
	if (par->match->checkentry != NULL) {
		ret = par->match->checkentry(par);
		if (ret < 0)
			return ret;
		else if (ret > 0)
			/* Flag up potential errors. */
			return -EIO;
	}
	return 0;
}