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
typedef  int /*<<< orphan*/  u32 ;
struct sidtab_node {int /*<<< orphan*/  sid; int /*<<< orphan*/  context; } ;
struct sidtab {struct sidtab_node** cache; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int SIDTAB_CACHE_LEN ; 
 scalar_t__ context_cmp (int /*<<< orphan*/ *,struct context*) ; 
 int /*<<< orphan*/  sidtab_update_cache (struct sidtab*,struct sidtab_node*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u32 sidtab_search_cache(struct sidtab *s, struct context *context)
{
	int i;
	struct sidtab_node *node;

	for (i = 0; i < SIDTAB_CACHE_LEN; i++) {
		node = s->cache[i];
		if (unlikely(!node))
			return 0;
		if (context_cmp(&node->context, context)) {
			sidtab_update_cache(s, node, i);
			return node->sid;
		}
	}
	return 0;
}