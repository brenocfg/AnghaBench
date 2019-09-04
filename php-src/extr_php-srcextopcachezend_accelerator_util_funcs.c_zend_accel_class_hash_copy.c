#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_16__ {int line_start; int /*<<< orphan*/  filename; } ;
struct TYPE_17__ {TYPE_1__ user; } ;
struct TYPE_18__ {int ce_flags; int /*<<< orphan*/  name; TYPE_2__ info; } ;
typedef  TYPE_3__ zend_class_entry ;
struct TYPE_20__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
struct TYPE_19__ {int nNumUsed; scalar_t__ nInternalPointer; TYPE_5__* arData; } ;
struct TYPE_15__ {int /*<<< orphan*/  ignore_dups; } ;
typedef  TYPE_4__ HashTable ;
typedef  int CG ;
typedef  TYPE_5__ Bucket ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ IS_UNDEF ; 
 scalar_t__ UNEXPECTED (int) ; 
 TYPE_14__ ZCG (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_ANON_CLASS ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 TYPE_3__* Z_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _zend_hash_append_ptr (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  accel_directives ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  zend_get_object_type (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_extend (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_find_ex (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_set_compiled_filename (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_accel_class_hash_copy(HashTable *target, HashTable *source)
{
	Bucket *p, *end;
	zval *t;

	zend_hash_extend(target, target->nNumUsed + source->nNumUsed, 0);
	p = source->arData;
	end = p + source->nNumUsed;
	for (; p != end; p++) {
		if (UNEXPECTED(Z_TYPE(p->val) == IS_UNDEF)) continue;
		ZEND_ASSERT(p->key);
		t = zend_hash_find_ex(target, p->key, 1);
		if (UNEXPECTED(t != NULL)) {
			if (EXPECTED(ZSTR_LEN(p->key) > 0) && EXPECTED(ZSTR_VAL(p->key)[0] == 0)) {
				/* Mangled key - ignore and wait for runtime */
				continue;
			} else if (UNEXPECTED(!ZCG(accel_directives).ignore_dups)) {
				zend_class_entry *ce1 = Z_PTR(p->val);
				if (!(ce1->ce_flags & ZEND_ACC_ANON_CLASS)) {
					CG(in_compilation) = 1;
					zend_set_compiled_filename(ce1->info.user.filename);
					CG(zend_lineno) = ce1->info.user.line_start;
					zend_error(E_ERROR,
							"Cannot declare %s %s, because the name is already in use",
							zend_get_object_type(ce1), ZSTR_VAL(ce1->name));
					return;
				}
				continue;
			}
		} else {
			t = _zend_hash_append_ptr(target, p->key, Z_PTR(p->val));
		}
	}
	target->nInternalPointer = 0;
	return;
}