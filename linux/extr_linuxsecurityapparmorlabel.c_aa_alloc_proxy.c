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
struct aa_proxy {int /*<<< orphan*/  label; int /*<<< orphan*/  count; } ;
struct aa_label {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_label (struct aa_label*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct aa_proxy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct aa_proxy *aa_alloc_proxy(struct aa_label *label, gfp_t gfp)
{
	struct aa_proxy *new;

	new = kzalloc(sizeof(struct aa_proxy), gfp);
	if (new) {
		kref_init(&new->count);
		rcu_assign_pointer(new->label, aa_get_label(label));
	}
	return new;
}