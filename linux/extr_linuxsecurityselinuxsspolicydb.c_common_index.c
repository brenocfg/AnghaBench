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
struct policydb {struct flex_array** sym_val_to_name; TYPE_1__ p_commons; } ;
struct flex_array {int dummy; } ;
struct common_datum {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 size_t SYM_COMMONS ; 
 int __GFP_ZERO ; 
 scalar_t__ flex_array_put_ptr (struct flex_array*,scalar_t__,void*,int) ; 

__attribute__((used)) static int common_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct common_datum *comdatum;
	struct flex_array *fa;

	comdatum = datum;
	p = datap;
	if (!comdatum->value || comdatum->value > p->p_commons.nprim)
		return -EINVAL;

	fa = p->sym_val_to_name[SYM_COMMONS];
	if (flex_array_put_ptr(fa, comdatum->value - 1, key,
			       GFP_KERNEL | __GFP_ZERO))
		BUG();
	return 0;
}