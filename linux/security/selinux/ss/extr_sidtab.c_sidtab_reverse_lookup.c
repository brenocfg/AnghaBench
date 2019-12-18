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
typedef  size_t u32 ;
struct sidtab_convert_params {int (* func ) (struct context*,struct context*,int /*<<< orphan*/ ) ;struct sidtab* target; int /*<<< orphan*/  args; } ;
struct sidtab {size_t count; int /*<<< orphan*/  lock; struct sidtab_convert_params* convert; int /*<<< orphan*/ * roots; } ;
struct context {int /*<<< orphan*/  str; scalar_t__ len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOVERFLOW ; 
 size_t SIDTAB_MAX ; 
 scalar_t__ context_cmp (struct context*,struct context*) ; 
 int context_cpy (struct context*,struct context*) ; 
 int /*<<< orphan*/  context_destroy (struct context*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct context* sidtab_do_lookup (struct sidtab*,size_t,int) ; 
 int sidtab_find_context (int /*<<< orphan*/ ,size_t*,size_t,size_t,struct context*,size_t*) ; 
 size_t sidtab_level_from_count (size_t) ; 
 int /*<<< orphan*/  sidtab_rcache_push (struct sidtab*,size_t) ; 
 int sidtab_rcache_search (struct sidtab*,struct context*,size_t*) ; 
 size_t smp_load_acquire (size_t*) ; 
 int /*<<< orphan*/  smp_store_release (size_t*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct context*,struct context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sidtab_reverse_lookup(struct sidtab *s, struct context *context,
				 u32 *index)
{
	unsigned long flags;
	u32 count, count_locked, level, pos;
	struct sidtab_convert_params *convert;
	struct context *dst, *dst_convert;
	int rc;

	rc = sidtab_rcache_search(s, context, index);
	if (rc == 0)
		return 0;

	/* read entries only after reading count */
	count = smp_load_acquire(&s->count);
	level = sidtab_level_from_count(count);

	pos = 0;
	rc = sidtab_find_context(s->roots[level], &pos, count, level,
				 context, index);
	if (rc == 0) {
		sidtab_rcache_push(s, *index);
		return 0;
	}

	/* lock-free search failed: lock, re-search, and insert if not found */
	spin_lock_irqsave(&s->lock, flags);

	convert = s->convert;
	count_locked = s->count;
	level = sidtab_level_from_count(count_locked);

	/* if count has changed before we acquired the lock, then catch up */
	while (count < count_locked) {
		if (context_cmp(sidtab_do_lookup(s, count, 0), context)) {
			sidtab_rcache_push(s, count);
			*index = count;
			rc = 0;
			goto out_unlock;
		}
		++count;
	}

	/* bail out if we already reached max entries */
	rc = -EOVERFLOW;
	if (count >= SIDTAB_MAX)
		goto out_unlock;

	/* insert context into new entry */
	rc = -ENOMEM;
	dst = sidtab_do_lookup(s, count, 1);
	if (!dst)
		goto out_unlock;

	rc = context_cpy(dst, context);
	if (rc)
		goto out_unlock;

	/*
	 * if we are building a new sidtab, we need to convert the context
	 * and insert it there as well
	 */
	if (convert) {
		rc = -ENOMEM;
		dst_convert = sidtab_do_lookup(convert->target, count, 1);
		if (!dst_convert) {
			context_destroy(dst);
			goto out_unlock;
		}

		rc = convert->func(context, dst_convert, convert->args);
		if (rc) {
			context_destroy(dst);
			goto out_unlock;
		}

		/* at this point we know the insert won't fail */
		convert->target->count = count + 1;
	}

	if (context->len)
		pr_info("SELinux:  Context %s is not valid (left unmapped).\n",
			context->str);

	sidtab_rcache_push(s, count);
	*index = count;

	/* write entries before writing new count */
	smp_store_release(&s->count, count + 1);

	rc = 0;
out_unlock:
	spin_unlock_irqrestore(&s->lock, flags);
	return rc;
}