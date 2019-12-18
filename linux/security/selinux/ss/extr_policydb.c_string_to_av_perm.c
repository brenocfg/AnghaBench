#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int nprim; } ;
struct policydb {struct class_datum** class_val_to_struct; TYPE_3__ p_classes; } ;
struct perm_datum {int value; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct common_datum {TYPE_1__ permissions; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct class_datum {TYPE_2__ permissions; struct common_datum* comdatum; } ;

/* Variables and functions */
 struct perm_datum* hashtab_search (int /*<<< orphan*/ ,char const*) ; 

u32 string_to_av_perm(struct policydb *p, u16 tclass, const char *name)
{
	struct class_datum *cladatum;
	struct perm_datum *perdatum = NULL;
	struct common_datum *comdatum;

	if (!tclass || tclass > p->p_classes.nprim)
		return 0;

	cladatum = p->class_val_to_struct[tclass-1];
	comdatum = cladatum->comdatum;
	if (comdatum)
		perdatum = hashtab_search(comdatum->permissions.table,
					  name);
	if (!perdatum)
		perdatum = hashtab_search(cladatum->permissions.table,
					  name);
	if (!perdatum)
		return 0;

	return 1U << (perdatum->value-1);
}