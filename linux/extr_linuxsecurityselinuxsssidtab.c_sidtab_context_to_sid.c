#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sidtab {scalar_t__ next_sid; int /*<<< orphan*/  lock; scalar_t__ shutdown; } ;
struct context {int /*<<< orphan*/  str; scalar_t__ len; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ SECSID_NULL ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int sidtab_insert (struct sidtab*,scalar_t__,struct context*) ; 
 scalar_t__ sidtab_search_cache (struct sidtab*,struct context*) ; 
 scalar_t__ sidtab_search_context (struct sidtab*,struct context*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int sidtab_context_to_sid(struct sidtab *s,
			  struct context *context,
			  u32 *out_sid)
{
	u32 sid;
	int ret = 0;
	unsigned long flags;

	*out_sid = SECSID_NULL;

	sid  = sidtab_search_cache(s, context);
	if (!sid)
		sid = sidtab_search_context(s, context);
	if (!sid) {
		spin_lock_irqsave(&s->lock, flags);
		/* Rescan now that we hold the lock. */
		sid = sidtab_search_context(s, context);
		if (sid)
			goto unlock_out;
		/* No SID exists for the context.  Allocate a new one. */
		if (s->next_sid == UINT_MAX || s->shutdown) {
			ret = -ENOMEM;
			goto unlock_out;
		}
		sid = s->next_sid++;
		if (context->len)
			pr_info("SELinux:  Context %s is not valid (left unmapped).\n",
			       context->str);
		ret = sidtab_insert(s, sid, context);
		if (ret)
			s->next_sid--;
unlock_out:
		spin_unlock_irqrestore(&s->lock, flags);
	}

	if (ret)
		return ret;

	*out_sid = sid;
	return 0;
}