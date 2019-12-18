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
struct sidtab {int /*<<< orphan*/ * rcache; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t SIDTAB_MAX ; 
 size_t SIDTAB_RCACHE_SIZE ; 
 scalar_t__ context_cmp (int /*<<< orphan*/ ,struct context*) ; 
 int /*<<< orphan*/  sidtab_do_lookup (struct sidtab*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sidtab_rcache_update (struct sidtab*,size_t,size_t) ; 

__attribute__((used)) static int sidtab_rcache_search(struct sidtab *s, struct context *context,
				u32 *index)
{
	u32 i;

	for (i = 0; i < SIDTAB_RCACHE_SIZE; i++) {
		u32 v = READ_ONCE(s->rcache[i]);

		if (v >= SIDTAB_MAX)
			continue;

		if (context_cmp(sidtab_do_lookup(s, v, 0), context)) {
			sidtab_rcache_update(s, v, i);
			*index = v;
			return 0;
		}
	}
	return -ENOENT;
}