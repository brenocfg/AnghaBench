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
struct ip_vs_dh_state {struct ip_vs_dh_bucket* buckets; } ;
struct ip_vs_dh_bucket {int /*<<< orphan*/  dest; } ;
struct ip_vs_dest {int dummy; } ;

/* Variables and functions */
 int IP_VS_DH_TAB_SIZE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_dest_put (struct ip_vs_dest*) ; 
 struct ip_vs_dest* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ip_vs_dh_flush(struct ip_vs_dh_state *s)
{
	int i;
	struct ip_vs_dh_bucket *b;
	struct ip_vs_dest *dest;

	b = &s->buckets[0];
	for (i=0; i<IP_VS_DH_TAB_SIZE; i++) {
		dest = rcu_dereference_protected(b->dest, 1);
		if (dest) {
			ip_vs_dest_put(dest);
			RCU_INIT_POINTER(b->dest, NULL);
		}
		b++;
	}
}