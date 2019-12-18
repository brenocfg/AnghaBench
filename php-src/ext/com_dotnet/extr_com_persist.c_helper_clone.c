#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_7__ {int /*<<< orphan*/  ce; } ;
struct TYPE_6__ {scalar_t__ unk; scalar_t__ ipsi; scalar_t__ ips; scalar_t__ ipf; TYPE_2__ std; } ;
typedef  TYPE_1__ php_com_persist_helper ;

/* Variables and functions */
 int /*<<< orphan*/  IPersistFile_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  IPersistStreamInit_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  IPersistStream_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  IUnknown_AddRef (scalar_t__) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object* helper_clone(zend_object *obj)
{
	php_com_persist_helper *clone, *object = (php_com_persist_helper*) obj;

	clone = emalloc(sizeof(*object));
	memcpy(clone, object, sizeof(*object));

	zend_object_std_init(&clone->std, object->std.ce);

	if (clone->ipf) {
		IPersistFile_AddRef(clone->ipf);
	}
	if (clone->ips) {
		IPersistStream_AddRef(clone->ips);
	}
	if (clone->ipsi) {
		IPersistStreamInit_AddRef(clone->ipsi);
	}
	if (clone->unk) {
		IUnknown_AddRef(clone->unk);
	}
	return (zend_object*)clone;
}