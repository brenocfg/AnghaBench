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
struct TYPE_2__ {int nprim; } ;
struct policydb {struct cond_bool_datum** bool_val_to_struct; struct flex_array** sym_val_to_name; TYPE_1__ p_bools; } ;
struct flex_array {int dummy; } ;
struct cond_bool_datum {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 size_t SYM_BOOLS ; 
 int __GFP_ZERO ; 
 scalar_t__ flex_array_put_ptr (struct flex_array*,int,void*,int) ; 

int cond_index_bool(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct cond_bool_datum *booldatum;
	struct flex_array *fa;

	booldatum = datum;
	p = datap;

	if (!booldatum->value || booldatum->value > p->p_bools.nprim)
		return -EINVAL;

	fa = p->sym_val_to_name[SYM_BOOLS];
	if (flex_array_put_ptr(fa, booldatum->value - 1, key,
			       GFP_KERNEL | __GFP_ZERO))
		BUG();
	p->bool_val_to_struct[booldatum->value - 1] = booldatum;

	return 0;
}