#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nprim; } ;
struct policydb {struct flex_array** sym_val_to_name; TYPE_1__ p_levels; } ;
struct level_datum {TYPE_2__* level; int /*<<< orphan*/  isalias; } ;
struct flex_array {int dummy; } ;
struct TYPE_4__ {scalar_t__ sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int GFP_KERNEL ; 
 size_t SYM_LEVELS ; 
 int __GFP_ZERO ; 
 scalar_t__ flex_array_put_ptr (struct flex_array*,scalar_t__,void*,int) ; 

__attribute__((used)) static int sens_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct level_datum *levdatum;
	struct flex_array *fa;

	levdatum = datum;
	p = datap;

	if (!levdatum->isalias) {
		if (!levdatum->level->sens ||
		    levdatum->level->sens > p->p_levels.nprim)
			return -EINVAL;
		fa = p->sym_val_to_name[SYM_LEVELS];
		if (flex_array_put_ptr(fa, levdatum->level->sens - 1, key,
				       GFP_KERNEL | __GFP_ZERO))
			BUG();
	}

	return 0;
}