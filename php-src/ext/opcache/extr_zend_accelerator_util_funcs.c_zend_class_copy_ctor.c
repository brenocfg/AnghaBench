#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {int num_excludes; } ;
typedef  TYPE_1__ zend_trait_precedence ;
typedef  TYPE_1__ zend_trait_alias ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  TYPE_1__ zend_class_name ;
struct TYPE_11__ {int refcount; int ce_flags; int default_properties_count; int default_static_members_count; int num_interfaces; int num_traits; TYPE_1__** trait_precedences; TYPE_1__** trait_aliases; TYPE_1__* trait_names; struct TYPE_11__** interfaces; TYPE_1__* interface_names; struct TYPE_11__** properties_info_table; int /*<<< orphan*/  constants_table; int /*<<< orphan*/  properties_info; int /*<<< orphan*/ * default_static_members_table; int /*<<< orphan*/  static_members_table; struct TYPE_11__* parent; int /*<<< orphan*/  function_table; int /*<<< orphan*/ * default_properties_table; } ;
typedef  TYPE_4__ zend_class_entry ;
typedef  size_t uint32_t ;

/* Variables and functions */
 void* ARENA_REALLOC (TYPE_4__*) ; 
 scalar_t__ IN_ARENA (TYPE_4__*) ; 
 int ZEND_ACC_LINKED ; 
 int /*<<< orphan*/  ZEND_MAP_PTR_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE_PROP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_INDIRECT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __call ; 
 int /*<<< orphan*/  __callstatic ; 
 int /*<<< orphan*/  __debugInfo ; 
 int /*<<< orphan*/  __get ; 
 int /*<<< orphan*/  __isset ; 
 int /*<<< orphan*/  __set ; 
 int /*<<< orphan*/  __tostring ; 
 int /*<<< orphan*/  __unset ; 
 int /*<<< orphan*/  clone ; 
 int /*<<< orphan*/  constructor ; 
 int /*<<< orphan*/  destructor ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  serialize_func ; 
 int /*<<< orphan*/  unserialize_func ; 
 int /*<<< orphan*/  zend_hash_clone_constants (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_clone_methods (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_clone_prop_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_update_inherited_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_class_copy_ctor(zend_class_entry **pce)
{
	zend_class_entry *ce = *pce;
	zval *src, *dst, *end;

	*pce = ce = ARENA_REALLOC(ce);
	ce->refcount = 1;

	if ((ce->ce_flags & ZEND_ACC_LINKED) && IN_ARENA(ce->parent)) {
		ce->parent = ARENA_REALLOC(ce->parent);
	}

	if (ce->default_properties_table) {
		dst = emalloc(sizeof(zval) * ce->default_properties_count);
		src = ce->default_properties_table;
		end = src + ce->default_properties_count;
		ce->default_properties_table = dst;
		for (; src != end; src++, dst++) {
			ZVAL_COPY_VALUE_PROP(dst, src);
		}
	}

	zend_hash_clone_methods(&ce->function_table);

	/* static members */
	if (ce->default_static_members_table) {
		int i, end;
		zend_class_entry *parent = !(ce->ce_flags & ZEND_ACC_LINKED) ? NULL : ce->parent;

		dst = emalloc(sizeof(zval) * ce->default_static_members_count);
		src = ce->default_static_members_table;
		ce->default_static_members_table = dst;
		i = ce->default_static_members_count - 1;

		/* Copy static properties in this class */
		end = parent ? parent->default_static_members_count : 0;
		for (; i >= end; i--) {
			zval *p = &dst[i];
			ZVAL_COPY_VALUE(p, &src[i]);
		}

		/* Create indirections to static properties from parent classes */
		while (parent && parent->default_static_members_table) {
			end = parent->parent ? parent->parent->default_static_members_count : 0;
			for (; i >= end; i--) {
				zval *p = &dst[i];
				ZVAL_INDIRECT(p, &parent->default_static_members_table[i]);
			}

			parent = parent->parent;
		}
	}
	ZEND_MAP_PTR_INIT(ce->static_members_table, &ce->default_static_members_table);

	/* properties_info */
	zend_hash_clone_prop_info(&ce->properties_info);

	/* constants table */
	zend_hash_clone_constants(&ce->constants_table);

	if (ce->properties_info_table) {
		int i;
		ce->properties_info_table = ARENA_REALLOC(ce->properties_info_table);
		for (i = 0; i < ce->default_properties_count; i++) {
			if (IN_ARENA(ce->properties_info_table[i])) {
				ce->properties_info_table[i] = ARENA_REALLOC(ce->properties_info_table[i]);
			}
		}
	}

	if (ce->num_interfaces) {
		zend_class_name *interface_names;

		if (!(ce->ce_flags & ZEND_ACC_LINKED)) {
			interface_names = emalloc(sizeof(zend_class_name) * ce->num_interfaces);
			memcpy(interface_names, ce->interface_names, sizeof(zend_class_name) * ce->num_interfaces);
			ce->interface_names = interface_names;
		} else {
			zend_class_entry **interfaces = emalloc(sizeof(zend_class_entry*) * ce->num_interfaces);
			uint32_t i;

			for (i = 0; i < ce->num_interfaces; i++) {
				if (IN_ARENA(ce->interfaces[i])) {
					interfaces[i] = ARENA_REALLOC(ce->interfaces[i]);
				} else {
					interfaces[i] = ce->interfaces[i];
				}
			}
			ce->interfaces = interfaces;
		}
	}

	zend_update_inherited_handler(constructor);
	zend_update_inherited_handler(destructor);
	zend_update_inherited_handler(clone);
	zend_update_inherited_handler(__get);
	zend_update_inherited_handler(__set);
	zend_update_inherited_handler(__call);
/* 5.1 stuff */
	zend_update_inherited_handler(serialize_func);
	zend_update_inherited_handler(unserialize_func);
	zend_update_inherited_handler(__isset);
	zend_update_inherited_handler(__unset);
/* 5.2 stuff */
	zend_update_inherited_handler(__tostring);

/* 5.3 stuff */
	zend_update_inherited_handler(__callstatic);
	zend_update_inherited_handler(__debugInfo);

/* 5.4 traits */
	if (ce->num_traits) {
		zend_class_name *trait_names = emalloc(sizeof(zend_class_name) * ce->num_traits);

		memcpy(trait_names, ce->trait_names, sizeof(zend_class_name) * ce->num_traits);
		ce->trait_names = trait_names;

		if (ce->trait_aliases) {
			zend_trait_alias **trait_aliases;
			int i = 0;

			while (ce->trait_aliases[i]) {
				i++;
			}
			trait_aliases = emalloc(sizeof(zend_trait_alias*) * (i + 1));
			i = 0;
			while (ce->trait_aliases[i]) {
				trait_aliases[i] = emalloc(sizeof(zend_trait_alias));
				memcpy(trait_aliases[i], ce->trait_aliases[i], sizeof(zend_trait_alias));
				i++;
			}
			trait_aliases[i] = NULL;
			ce->trait_aliases = trait_aliases;
		}

		if (ce->trait_precedences) {
			zend_trait_precedence **trait_precedences;
			int i = 0;

			while (ce->trait_precedences[i]) {
				i++;
			}
			trait_precedences = emalloc(sizeof(zend_trait_precedence*) * (i + 1));
			i = 0;
			while (ce->trait_precedences[i]) {
				trait_precedences[i] = emalloc(sizeof(zend_trait_precedence) + (ce->trait_precedences[i]->num_excludes - 1) * sizeof(zend_string*));
				memcpy(trait_precedences[i], ce->trait_precedences[i], sizeof(zend_trait_precedence) + (ce->trait_precedences[i]->num_excludes - 1) * sizeof(zend_string*));
				i++;
			}
			trait_precedences[i] = NULL;
			ce->trait_precedences = trait_precedences;
		}
	}
}