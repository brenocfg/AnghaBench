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
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 int /*<<< orphan*/  r_list_add_sorted (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcmp ; 
 int /*<<< orphan*/ * ut64_new (int /*<<< orphan*/  const) ; 

__attribute__((used)) static bool regcb(void *u, const ut64 k, const void *v) {
	RList *sorted = (RList*) u;
	ut64 *n = ut64_new (k);
	r_list_add_sorted (sorted, n, regcmp);
	return true;
}