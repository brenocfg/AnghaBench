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
struct svc_rqst {int /*<<< orphan*/  rq_chandle; } ;
struct ent {int /*<<< orphan*/  h; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int cache_check (struct cache_detail*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,struct cache_detail*) ; 

__attribute__((used)) static int
idmap_lookup(struct svc_rqst *rqstp,
		struct ent *(*lookup_fn)(struct cache_detail *, struct ent *),
		struct ent *key, struct cache_detail *detail, struct ent **item)
{
	int ret;

	*item = lookup_fn(detail, key);
	if (!*item)
		return -ENOMEM;
 retry:
	ret = cache_check(detail, &(*item)->h, &rqstp->rq_chandle);

	if (ret == -ETIMEDOUT) {
		struct ent *prev_item = *item;
		*item = lookup_fn(detail, key);
		if (*item != prev_item)
			goto retry;
		cache_put(&(*item)->h, detail);
	}
	return ret;
}