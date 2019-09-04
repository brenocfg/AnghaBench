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
struct dn_zone {int dummy; } ;
struct dn_fib_node {struct dn_fib_node* fn_next; int /*<<< orphan*/  fn_key; } ;

/* Variables and functions */
 struct dn_fib_node** dn_chain_p (int /*<<< orphan*/ ,struct dn_zone*) ; 
 scalar_t__ dn_key_leq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dn_rebuild_zone(struct dn_zone *dz,
				   struct dn_fib_node **old_ht,
				   int old_divisor)
{
	struct dn_fib_node *f, **fp, *next;
	int i;

	for(i = 0; i < old_divisor; i++) {
		for(f = old_ht[i]; f; f = next) {
			next = f->fn_next;
			for(fp = dn_chain_p(f->fn_key, dz);
				*fp && dn_key_leq((*fp)->fn_key, f->fn_key);
				fp = &(*fp)->fn_next)
				/* NOTHING */;
			f->fn_next = *fp;
			*fp = f;
		}
	}
}