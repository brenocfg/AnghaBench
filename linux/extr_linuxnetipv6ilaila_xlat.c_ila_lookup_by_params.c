#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  locator_match; } ;
struct ila_xlat_params {TYPE_2__ ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  rhash_table; } ;
struct ila_net {TYPE_1__ xlat; } ;
struct ila_map {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ila_cmp_params (struct ila_map*,struct ila_xlat_params*) ; 
 struct ila_map* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct ila_map* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rht_params ; 

__attribute__((used)) static inline struct ila_map *ila_lookup_by_params(struct ila_xlat_params *xp,
						   struct ila_net *ilan)
{
	struct ila_map *ila;

	ila = rhashtable_lookup_fast(&ilan->xlat.rhash_table,
				     &xp->ip.locator_match,
				     rht_params);
	while (ila) {
		if (!ila_cmp_params(ila, xp))
			return ila;
		ila = rcu_access_pointer(ila->next);
	}

	return NULL;
}