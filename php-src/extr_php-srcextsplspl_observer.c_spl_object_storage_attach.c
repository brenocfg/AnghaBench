#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_17__ {int /*<<< orphan*/  h; scalar_t__ key; } ;
typedef  TYPE_1__ zend_hash_key ;
struct TYPE_18__ {int /*<<< orphan*/  inf; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ spl_SplObjectStorageElement ;
struct TYPE_19__ {int /*<<< orphan*/  storage; } ;
typedef  TYPE_3__ spl_SplObjectStorage ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_object_storage_free_hash (TYPE_3__*,TYPE_1__*) ; 
 TYPE_2__* spl_object_storage_get (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ spl_object_storage_get_hash (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_hash_index_update_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* zend_hash_update_mem (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

spl_SplObjectStorageElement *spl_object_storage_attach(spl_SplObjectStorage *intern, zval *obj, zval *inf) /* {{{ */
{
	spl_SplObjectStorageElement *pelement, element;
	zend_hash_key key;
	if (spl_object_storage_get_hash(&key, intern, obj) == FAILURE) {
		return NULL;
	}

	pelement = spl_object_storage_get(intern, &key);

	if (pelement) {
		zval_ptr_dtor(&pelement->inf);
		if (inf) {
			ZVAL_COPY(&pelement->inf, inf);
		} else {
			ZVAL_NULL(&pelement->inf);
		}
		spl_object_storage_free_hash(intern, &key);
		return pelement;
	}

	ZVAL_COPY(&element.obj, obj);
	if (inf) {
		ZVAL_COPY(&element.inf, inf);
	} else {
		ZVAL_NULL(&element.inf);
	}
	if (key.key) {
		pelement = zend_hash_update_mem(&intern->storage, key.key, &element, sizeof(spl_SplObjectStorageElement));
	} else {
		pelement = zend_hash_index_update_mem(&intern->storage, key.h, &element, sizeof(spl_SplObjectStorageElement));
	}
	spl_object_storage_free_hash(intern, &key);
	return pelement;
}