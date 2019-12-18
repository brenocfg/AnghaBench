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
struct xt_tgchk_param {size_t family; int hook_mask; TYPE_1__* target; int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  allow ;
struct TYPE_2__ {int hooks; int (* checkentry ) (struct xt_tgchk_param*) ;int /*<<< orphan*/  proto; int /*<<< orphan*/  name; int /*<<< orphan*/ * table; int /*<<< orphan*/  targetsize; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int XT_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct xt_tgchk_param*) ; 
 int /*<<< orphan*/  textify_hooks (char*,int,int,size_t) ; 
 int /*<<< orphan*/ * xt_prefix ; 

int xt_check_target(struct xt_tgchk_param *par,
		    unsigned int size, u16 proto, bool inv_proto)
{
	int ret;

	if (XT_ALIGN(par->target->targetsize) != size) {
		pr_err_ratelimited("%s_tables: %s.%u target: invalid size %u (kernel) != (user) %u\n",
				   xt_prefix[par->family], par->target->name,
				   par->target->revision,
				   XT_ALIGN(par->target->targetsize), size);
		return -EINVAL;
	}
	if (par->target->table != NULL &&
	    strcmp(par->target->table, par->table) != 0) {
		pr_info_ratelimited("%s_tables: %s target: only valid in %s table, not %s\n",
				    xt_prefix[par->family], par->target->name,
				    par->target->table, par->table);
		return -EINVAL;
	}
	if (par->target->hooks && (par->hook_mask & ~par->target->hooks) != 0) {
		char used[64], allow[64];

		pr_info_ratelimited("%s_tables: %s target: used from hooks %s, but only usable from %s\n",
				    xt_prefix[par->family], par->target->name,
				    textify_hooks(used, sizeof(used),
						  par->hook_mask, par->family),
				    textify_hooks(allow, sizeof(allow),
						  par->target->hooks,
						  par->family));
		return -EINVAL;
	}
	if (par->target->proto && (par->target->proto != proto || inv_proto)) {
		pr_info_ratelimited("%s_tables: %s target: only valid for protocol %u\n",
				    xt_prefix[par->family], par->target->name,
				    par->target->proto);
		return -EINVAL;
	}
	if (par->target->checkentry != NULL) {
		ret = par->target->checkentry(par);
		if (ret < 0)
			return ret;
		else if (ret > 0)
			/* Flag up potential errors. */
			return -EIO;
	}
	return 0;
}