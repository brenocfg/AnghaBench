#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user_datum {int /*<<< orphan*/  range; } ;
struct TYPE_2__ {int nprim; } ;
struct policydb {struct user_datum** user_val_to_struct; TYPE_1__ p_users; int /*<<< orphan*/  mls_enabled; } ;
struct context {scalar_t__ role; int user; int /*<<< orphan*/  range; } ;

/* Variables and functions */
 scalar_t__ OBJECT_R_VAL ; 
 int /*<<< orphan*/  mls_range_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mls_range_isvalid (struct policydb*,int /*<<< orphan*/ *) ; 

int mls_context_isvalid(struct policydb *p, struct context *c)
{
	struct user_datum *usrdatum;

	if (!p->mls_enabled)
		return 1;

	if (!mls_range_isvalid(p, &c->range))
		return 0;

	if (c->role == OBJECT_R_VAL)
		return 1;

	/*
	 * User must be authorized for the MLS range.
	 */
	if (!c->user || c->user > p->p_users.nprim)
		return 0;
	usrdatum = p->user_val_to_struct[c->user - 1];
	if (!mls_range_contains(usrdatum->range, c->range))
		return 0; /* user may not be associated with range */

	return 1;
}