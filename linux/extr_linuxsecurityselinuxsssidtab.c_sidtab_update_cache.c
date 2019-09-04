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
struct sidtab_node {int dummy; } ;
struct sidtab {struct sidtab_node** cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SIDTAB_CACHE_LEN ; 

__attribute__((used)) static void sidtab_update_cache(struct sidtab *s, struct sidtab_node *n, int loc)
{
	BUG_ON(loc >= SIDTAB_CACHE_LEN);

	while (loc > 0) {
		s->cache[loc] = s->cache[loc - 1];
		loc--;
	}
	s->cache[0] = n;
}