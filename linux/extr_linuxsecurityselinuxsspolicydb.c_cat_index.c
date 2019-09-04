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
struct TYPE_2__ {scalar_t__ nprim; } ;
struct policydb {struct flex_array** sym_val_to_name; TYPE_1__ p_cats; } ;
struct flex_array {int dummy; } ;
struct cat_datum {scalar_t__ value; int /*<<< orphan*/  isalias; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 size_t SYM_CATS ; 
 int __GFP_ZERO ; 
 scalar_t__ flex_array_put_ptr (struct flex_array*,scalar_t__,void*,int) ; 

__attribute__((used)) static int cat_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct cat_datum *catdatum;
	struct flex_array *fa;

	catdatum = datum;
	p = datap;

	if (!catdatum->isalias) {
		if (!catdatum->value || catdatum->value > p->p_cats.nprim)
			return -EINVAL;
		fa = p->sym_val_to_name[SYM_CATS];
		if (flex_array_put_ptr(fa, catdatum->value - 1, key,
				       GFP_KERNEL | __GFP_ZERO))
			BUG();
	}

	return 0;
}