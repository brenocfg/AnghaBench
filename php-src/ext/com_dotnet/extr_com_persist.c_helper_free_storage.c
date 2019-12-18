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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_2__ {int /*<<< orphan*/  std; scalar_t__ unk; scalar_t__ ipsi; scalar_t__ ips; scalar_t__ ipf; } ;
typedef  TYPE_1__ php_com_persist_helper ;

/* Variables and functions */
 int /*<<< orphan*/  IPersistFile_Release (scalar_t__) ; 
 int /*<<< orphan*/  IPersistStreamInit_Release (scalar_t__) ; 
 int /*<<< orphan*/  IPersistStream_Release (scalar_t__) ; 
 int /*<<< orphan*/  IUnknown_Release (scalar_t__) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void helper_free_storage(zend_object *obj)
{
	php_com_persist_helper *object = (php_com_persist_helper*)obj;

	if (object->ipf) {
		IPersistFile_Release(object->ipf);
	}
	if (object->ips) {
		IPersistStream_Release(object->ips);
	}
	if (object->ipsi) {
		IPersistStreamInit_Release(object->ipsi);
	}
	if (object->unk) {
		IUnknown_Release(object->unk);
	}
	zend_object_std_dtor(&object->std);
}