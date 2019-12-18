#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ class_name; scalar_t__ method_name; } ;
struct TYPE_14__ {scalar_t__ doc_comment; scalar_t__ filename; } ;
struct TYPE_15__ {TYPE_1__ user; } ;
struct TYPE_17__ {int ce_flags; int default_properties_count; int default_static_members_count; size_t num_interfaces; size_t num_traits; size_t num_excludes; struct TYPE_17__* default_static_members_table; int /*<<< orphan*/  static_members_table; struct TYPE_17__* zf_next; struct TYPE_17__* iterator_funcs_ptr; struct TYPE_17__* zf_current; struct TYPE_17__* zf_key; struct TYPE_17__* zf_valid; struct TYPE_17__* zf_rewind; struct TYPE_17__* zf_new_iterator; int /*<<< orphan*/  unserialize; int /*<<< orphan*/  serialize; struct TYPE_17__* __debugInfo; struct TYPE_17__* __callstatic; struct TYPE_17__* __tostring; struct TYPE_17__* __unset; struct TYPE_17__* __isset; struct TYPE_17__* unserialize_func; struct TYPE_17__* serialize_func; struct TYPE_17__* __call; struct TYPE_17__* __set; struct TYPE_17__* __get; struct TYPE_17__* clone; struct TYPE_17__* destructor; struct TYPE_17__* constructor; scalar_t__* exclude_class_names; TYPE_3__ trait_method; struct TYPE_17__** trait_precedences; scalar_t__ alias; struct TYPE_17__** trait_aliases; scalar_t__ lc_name; struct TYPE_17__* trait_names; scalar_t__ name; struct TYPE_17__* interface_names; struct TYPE_17__** properties_info_table; int /*<<< orphan*/  properties_info; TYPE_2__ info; int /*<<< orphan*/  constants_table; struct TYPE_17__* default_properties_table; int /*<<< orphan*/  function_table; struct TYPE_17__* parent; scalar_t__ parent_name; } ;
typedef  TYPE_4__ zval ;
typedef  TYPE_4__ zend_trait_precedence ;
typedef  TYPE_4__ zend_trait_alias ;
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  TYPE_4__ zend_class_entry ;
typedef  size_t uint32_t ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (int) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_4__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_STR (scalar_t__) ; 
 int ZEND_ACC_ANON_CLASS ; 
 int ZEND_ACC_IMMUTABLE ; 
 int ZEND_ACC_LINKED ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/ * ZEND_FUNCTION_DTOR ; 
 int /*<<< orphan*/  ZEND_MAP_PTR_INIT (int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  ZEND_MAP_PTR_NEW (int /*<<< orphan*/ ) ; 
 TYPE_4__* Z_PTR_P (TYPE_4__*) ; 
 int /*<<< orphan*/  zend_class_serialize_deny ; 
 int /*<<< orphan*/  zend_class_unserialize_deny ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_class_constant ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_func ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_prop_info ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_zval (TYPE_4__*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_unserialize_class(zval                    *zv,
                                              zend_persistent_script  *script,
                                              void                    *buf)
{
	zend_class_entry *ce;
	zend_class_entry *parent = NULL;

	UNSERIALIZE_PTR(Z_PTR_P(zv));
	ce = Z_PTR_P(zv);

	UNSERIALIZE_STR(ce->name);
	if (ce->parent) {
		if (!(ce->ce_flags & ZEND_ACC_LINKED)) {
			UNSERIALIZE_STR(ce->parent_name);
		} else {
			UNSERIALIZE_PTR(ce->parent);
			parent = ce->parent;
		}
	}
	zend_file_cache_unserialize_hash(&ce->function_table,
			script, buf, zend_file_cache_unserialize_func, ZEND_FUNCTION_DTOR);
	if (ce->default_properties_table) {
		zval *p, *end;

		UNSERIALIZE_PTR(ce->default_properties_table);
		p = ce->default_properties_table;
		end = p + ce->default_properties_count;
		while (p < end) {
			zend_file_cache_unserialize_zval(p, script, buf);
			p++;
		}
	}
	if (ce->default_static_members_table) {
		zval *table, *p, *end;

		/* Unserialize only static properties in this class.
		 * Static properties from parent classes will be handled in class_copy_ctor */
		UNSERIALIZE_PTR(ce->default_static_members_table);
		table = ce->default_static_members_table;
		p = table + (parent ? parent->default_static_members_count : 0);
		end = table + ce->default_static_members_count;
		while (p < end) {
			zend_file_cache_unserialize_zval(p, script, buf);
			p++;
		}
	}
	zend_file_cache_unserialize_hash(&ce->constants_table,
			script, buf, zend_file_cache_unserialize_class_constant, NULL);
	UNSERIALIZE_STR(ce->info.user.filename);
	UNSERIALIZE_STR(ce->info.user.doc_comment);
	zend_file_cache_unserialize_hash(&ce->properties_info,
			script, buf, zend_file_cache_unserialize_prop_info, NULL);

	if (ce->properties_info_table) {
		uint32_t i;
		UNSERIALIZE_PTR(ce->properties_info_table);

		for (i = 0; i < ce->default_properties_count; i++) {
			UNSERIALIZE_PTR(ce->properties_info_table[i]);
		}
	}

	if (ce->num_interfaces) {
		uint32_t i;

		ZEND_ASSERT(!(ce->ce_flags & ZEND_ACC_LINKED));
		UNSERIALIZE_PTR(ce->interface_names);

		for (i = 0; i < ce->num_interfaces; i++) {
			UNSERIALIZE_STR(ce->interface_names[i].name);
			UNSERIALIZE_STR(ce->interface_names[i].lc_name);
		}
	}

	if (ce->num_traits) {
		uint32_t i;

		UNSERIALIZE_PTR(ce->trait_names);

		for (i = 0; i < ce->num_traits; i++) {
			UNSERIALIZE_STR(ce->trait_names[i].name);
			UNSERIALIZE_STR(ce->trait_names[i].lc_name);
		}

		if (ce->trait_aliases) {
			zend_trait_alias **p, *q;

			UNSERIALIZE_PTR(ce->trait_aliases);
			p = ce->trait_aliases;

			while (*p) {
				UNSERIALIZE_PTR(*p);
				q = *p;

				if (q->trait_method.method_name) {
					UNSERIALIZE_STR(q->trait_method.method_name);
				}
				if (q->trait_method.class_name) {
					UNSERIALIZE_STR(q->trait_method.class_name);
				}

				if (q->alias) {
					UNSERIALIZE_STR(q->alias);
				}
				p++;
			}
		}

		if (ce->trait_precedences) {
			zend_trait_precedence **p, *q;
			uint32_t j;

			UNSERIALIZE_PTR(ce->trait_precedences);
			p = ce->trait_precedences;

			while (*p) {
				UNSERIALIZE_PTR(*p);
				q = *p;

				if (q->trait_method.method_name) {
					UNSERIALIZE_STR(q->trait_method.method_name);
				}
				if (q->trait_method.class_name) {
					UNSERIALIZE_STR(q->trait_method.class_name);
				}

				for (j = 0; j < q->num_excludes; j++) {
					UNSERIALIZE_STR(q->exclude_class_names[j]);
				}
				p++;
			}
		}
	}

	UNSERIALIZE_PTR(ce->constructor);
	UNSERIALIZE_PTR(ce->destructor);
	UNSERIALIZE_PTR(ce->clone);
	UNSERIALIZE_PTR(ce->__get);
	UNSERIALIZE_PTR(ce->__set);
	UNSERIALIZE_PTR(ce->__call);
	UNSERIALIZE_PTR(ce->serialize_func);
	UNSERIALIZE_PTR(ce->unserialize_func);
	UNSERIALIZE_PTR(ce->__isset);
	UNSERIALIZE_PTR(ce->__unset);
	UNSERIALIZE_PTR(ce->__tostring);
	UNSERIALIZE_PTR(ce->__callstatic);
	UNSERIALIZE_PTR(ce->__debugInfo);

	if (UNEXPECTED((ce->ce_flags & ZEND_ACC_ANON_CLASS))) {
		ce->serialize = zend_class_serialize_deny;
		ce->unserialize = zend_class_unserialize_deny;
	}

	if (ce->iterator_funcs_ptr) {
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr);
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr->zf_new_iterator);
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr->zf_rewind);
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr->zf_valid);
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr->zf_key);
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr->zf_current);
		UNSERIALIZE_PTR(ce->iterator_funcs_ptr->zf_next);
	}

	if (ce->ce_flags & ZEND_ACC_IMMUTABLE && ce->default_static_members_table) {
		ZEND_MAP_PTR_NEW(ce->static_members_table);
	} else {
		ZEND_MAP_PTR_INIT(ce->static_members_table, &ce->default_static_members_table);
	}
}