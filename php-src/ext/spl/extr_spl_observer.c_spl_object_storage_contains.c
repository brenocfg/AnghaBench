#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {int /*<<< orphan*/  h; scalar_t__ key; } ;
typedef  TYPE_1__ zend_hash_key ;
struct TYPE_9__ {int /*<<< orphan*/  storage; } ;
typedef  TYPE_2__ spl_SplObjectStorage ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  spl_object_storage_free_hash (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ spl_object_storage_get_hash (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int zend_hash_exists (int /*<<< orphan*/ *,scalar_t__) ; 
 int zend_hash_index_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int spl_object_storage_contains(spl_SplObjectStorage *intern, zval *obj) /* {{{ */
{
	int found;
	zend_hash_key key;
	if (spl_object_storage_get_hash(&key, intern, obj) == FAILURE) {
		return 0;
	}

	if (key.key) {
		found = zend_hash_exists(&intern->storage, key.key);
	} else {
		found = zend_hash_index_exists(&intern->storage, key.h);
	}
	spl_object_storage_free_hash(intern, &key);
	return found;
}