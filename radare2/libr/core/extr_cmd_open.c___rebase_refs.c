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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  HtUP ;

/* Variables and functions */
 int /*<<< orphan*/  __rebase_refs_i ; 
 int /*<<< orphan*/  ht_up_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool __rebase_refs(void *user, const ut64 k, const void *v) {
	HtUP *ht = (HtUP *)v;
	ht_up_foreach (ht, __rebase_refs_i, user);
	return true;

}