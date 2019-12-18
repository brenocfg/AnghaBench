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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_9__ {int /*<<< orphan*/  std; int /*<<< orphan*/  dimensions; int /*<<< orphan*/  indices; TYPE_1__* obj; } ;
typedef  TYPE_2__ php_com_saproxy ;
struct TYPE_8__ {int /*<<< orphan*/  zo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_ADDREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clone_indices (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  safe_emalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object* saproxy_clone(zend_object *object)
{
	php_com_saproxy *proxy = (php_com_saproxy *) object;
	php_com_saproxy *cloneproxy;

	cloneproxy = emalloc(sizeof(*cloneproxy));
	memcpy(cloneproxy, proxy, sizeof(*cloneproxy));

	GC_ADDREF(&cloneproxy->obj->zo);
	cloneproxy->indices = safe_emalloc(cloneproxy->dimensions, sizeof(zval *), 0);
	clone_indices(cloneproxy, proxy, proxy->dimensions);

	return &cloneproxy->std;
}