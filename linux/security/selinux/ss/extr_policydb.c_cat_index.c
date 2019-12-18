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
struct policydb {void*** sym_val_to_name; TYPE_1__ p_cats; } ;
struct cat_datum {int value; int /*<<< orphan*/  isalias; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t SYM_CATS ; 

__attribute__((used)) static int cat_index(void *key, void *datum, void *datap)
{
	struct policydb *p;
	struct cat_datum *catdatum;

	catdatum = datum;
	p = datap;

	if (!catdatum->isalias) {
		if (!catdatum->value || catdatum->value > p->p_cats.nprim)
			return -EINVAL;

		p->sym_val_to_name[SYM_CATS][catdatum->value - 1] = key;
	}

	return 0;
}