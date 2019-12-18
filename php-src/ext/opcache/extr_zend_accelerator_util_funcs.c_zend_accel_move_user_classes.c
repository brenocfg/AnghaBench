#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_16__ {int /*<<< orphan*/ * filename; } ;
struct TYPE_21__ {int nNumUsed; int /*<<< orphan*/ * pDestructor; TYPE_7__* arData; } ;
struct TYPE_19__ {TYPE_1__ main_op_array; TYPE_6__ class_table; } ;
typedef  TYPE_4__ zend_script ;
struct TYPE_17__ {int /*<<< orphan*/ * filename; } ;
struct TYPE_18__ {TYPE_2__ user; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_3__ info; } ;
typedef  TYPE_5__ zend_class_entry ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/ * dtor_func_t ;
struct TYPE_22__ {int /*<<< orphan*/  key; int /*<<< orphan*/  val; } ;
typedef  TYPE_6__ HashTable ;
typedef  TYPE_7__ Bucket ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 scalar_t__ IS_UNDEF ; 
 scalar_t__ UNEXPECTED (int) ; 
 scalar_t__ ZEND_USER_CLASS ; 
 TYPE_5__* Z_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zend_hash_append_ptr (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  zend_hash_del_bucket (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  zend_hash_extend (TYPE_6__*,int,int /*<<< orphan*/ ) ; 

void zend_accel_move_user_classes(HashTable *src, uint32_t count, zend_script *script)
{
	Bucket *p, *end;
	HashTable *dst;
	zend_string *filename;
	dtor_func_t orig_dtor;
	zend_class_entry *ce;

	if (!count) {
		return;
	}

	dst = &script->class_table;
	filename = script->main_op_array.filename;
	orig_dtor = src->pDestructor;
	src->pDestructor = NULL;
	zend_hash_extend(dst, count, 0);
	end = src->arData + src->nNumUsed;
	p = end - count;
	for (; p != end; p++) {
		if (UNEXPECTED(Z_TYPE(p->val) == IS_UNDEF)) continue;
		ce = Z_PTR(p->val);
		if (EXPECTED(ce->type == ZEND_USER_CLASS)
		 && EXPECTED(ce->info.user.filename == filename)) {
			_zend_hash_append_ptr(dst, p->key, ce);
			zend_hash_del_bucket(src, p);
		}
	}
	src->pDestructor = orig_dtor;
}