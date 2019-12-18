#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/ * gcdata; int /*<<< orphan*/  storage; int /*<<< orphan*/  std; } ;
typedef  TYPE_1__ spl_SplObjectStorage ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 TYPE_1__* spl_object_storage_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void spl_SplObjectStorage_free_storage(zend_object *object) /* {{{ */
{
	spl_SplObjectStorage *intern = spl_object_storage_from_obj(object);

	zend_object_std_dtor(&intern->std);

	zend_hash_destroy(&intern->storage);

	if (intern->gcdata != NULL) {
		efree(intern->gcdata);
	}

}