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
struct user_datum {int value; scalar_t__ bounds; } ;
struct TYPE_2__ {int nprim; } ;
struct policydb {struct user_datum** user_val_to_struct; struct flex_array** sym_val_to_name; TYPE_1__ p_users; } ;
struct flex_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 size_t SYM_USERS ; 
 int __GFP_ZERO ; 
 scalar_t__ flex_array_put_ptr (struct flex_array*,int,void*,int) ; 

__attribute__((used)) static int user_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct user_datum *usrdatum;
	struct flex_array *fa;

	usrdatum = datum;
	p = datap;
	if (!usrdatum->value
	    || usrdatum->value > p->p_users.nprim
	    || usrdatum->bounds > p->p_users.nprim)
		return -EINVAL;

	fa = p->sym_val_to_name[SYM_USERS];
	if (flex_array_put_ptr(fa, usrdatum->value - 1, key,
			       GFP_KERNEL | __GFP_ZERO))
		BUG();
	p->user_val_to_struct[usrdatum->value - 1] = usrdatum;
	return 0;
}