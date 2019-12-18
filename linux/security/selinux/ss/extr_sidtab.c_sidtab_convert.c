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
typedef  size_t u32 ;
struct sidtab_convert_params {TYPE_1__* target; } ;
struct sidtab {size_t count; int /*<<< orphan*/  lock; struct sidtab_convert_params* convert; int /*<<< orphan*/ * roots; } ;
struct TYPE_2__ {size_t count; int /*<<< orphan*/ * roots; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  pr_info (char*,size_t) ; 
 int sidtab_convert_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t,size_t,struct sidtab_convert_params*) ; 
 scalar_t__ sidtab_do_lookup (TYPE_1__*,size_t,int) ; 
 size_t sidtab_level_from_count (size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int sidtab_convert(struct sidtab *s, struct sidtab_convert_params *params)
{
	unsigned long flags;
	u32 count, level, pos;
	int rc;

	spin_lock_irqsave(&s->lock, flags);

	/* concurrent policy loads are not allowed */
	if (s->convert) {
		spin_unlock_irqrestore(&s->lock, flags);
		return -EBUSY;
	}

	count = s->count;
	level = sidtab_level_from_count(count);

	/* allocate last leaf in the new sidtab (to avoid race with
	 * live convert)
	 */
	rc = sidtab_do_lookup(params->target, count - 1, 1) ? 0 : -ENOMEM;
	if (rc) {
		spin_unlock_irqrestore(&s->lock, flags);
		return rc;
	}

	/* set count in case no new entries are added during conversion */
	params->target->count = count;

	/* enable live convert of new entries */
	s->convert = params;

	/* we can safely do the rest of the conversion outside the lock */
	spin_unlock_irqrestore(&s->lock, flags);

	pr_info("SELinux:  Converting %u SID table entries...\n", count);

	/* convert all entries not covered by live convert */
	pos = 0;
	rc = sidtab_convert_tree(&params->target->roots[level],
				 &s->roots[level], &pos, count, level, params);
	if (rc) {
		/* we need to keep the old table - disable live convert */
		spin_lock_irqsave(&s->lock, flags);
		s->convert = NULL;
		spin_unlock_irqrestore(&s->lock, flags);
	}
	return rc;
}