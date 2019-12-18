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
struct lec_arp_table {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct lec_arp_table*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void lec_arp_put(struct lec_arp_table *entry)
{
	if (refcount_dec_and_test(&entry->usage))
		kfree(entry);
}