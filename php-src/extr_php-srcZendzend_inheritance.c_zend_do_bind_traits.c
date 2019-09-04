#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ num_traits; int ce_flags; int /*<<< orphan*/  name; TYPE_1__* trait_names; } ;
typedef  TYPE_2__ zend_class_entry ;
typedef  size_t uint32_t ;
struct TYPE_20__ {int /*<<< orphan*/  lc_name; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_TRAIT ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZEND_FETCH_CLASS_TRAIT ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_2__**) ; 
 TYPE_2__** emalloc (int) ; 
 int /*<<< orphan*/  zend_do_check_for_inconsistent_traits_aliasing (TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  zend_do_traits_method_binding (TYPE_2__*,TYPE_2__**,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  zend_do_traits_property_binding (TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zend_fetch_class_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_traits_init_trait_structures (TYPE_2__*,TYPE_2__**,TYPE_2__***,TYPE_2__***) ; 

__attribute__((used)) static void zend_do_bind_traits(zend_class_entry *ce) /* {{{ */
{
	HashTable **exclude_tables;
	zend_class_entry **aliases;
	zend_class_entry **traits, *trait;
	uint32_t i, j;

	ZEND_ASSERT(ce->num_traits > 0);

	traits = emalloc(sizeof(zend_class_entry*) * ce->num_traits);

	for (i = 0; i < ce->num_traits; i++) {
		trait = zend_fetch_class_by_name(ce->trait_names[i].name,
			ce->trait_names[i].lc_name, ZEND_FETCH_CLASS_TRAIT);
		if (UNEXPECTED(trait == NULL)) {
			return;
		}
		if (UNEXPECTED(!(trait->ce_flags & ZEND_ACC_TRAIT))) {
			zend_error_noreturn(E_ERROR, "%s cannot use %s - it is not a trait", ZSTR_VAL(ce->name), ZSTR_VAL(trait->name));
			return;
		}
		for (j = 0; j < i; j++) {
			if (traits[j] == trait) {
				/* skip duplications */
				trait = NULL;
				break;
			}
		}
		traits[i] = trait;
	}

	/* complete initialization of trait strutures in ce */
	zend_traits_init_trait_structures(ce, traits, &exclude_tables, &aliases);

	/* first care about all methods to be flattened into the class */
	zend_do_traits_method_binding(ce, traits, exclude_tables, aliases);

	/* Aliases which have not been applied indicate typos/bugs. */
	zend_do_check_for_inconsistent_traits_aliasing(ce, aliases);

	if (aliases) {
		efree(aliases);
	}

	if (exclude_tables) {
		efree(exclude_tables);
	}

	/* then flatten the properties into it, to, mostly to notfiy developer about problems */
	zend_do_traits_property_binding(ce, traits);

	efree(traits);
}