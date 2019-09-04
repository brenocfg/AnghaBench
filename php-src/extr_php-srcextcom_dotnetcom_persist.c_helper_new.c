#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_8__ {TYPE_1__ std; } ;
typedef  TYPE_2__ php_com_persist_helper ;

/* Variables and functions */
 TYPE_2__* emalloc (int) ; 
 int /*<<< orphan*/  helper_ce ; 
 int /*<<< orphan*/  helper_handlers ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object* helper_new(zend_class_entry *ce)
{
	php_com_persist_helper *helper;

	helper = emalloc(sizeof(*helper));
	memset(helper, 0, sizeof(*helper));

	zend_object_std_init(&helper->std, helper_ce);
	helper->std.handlers = &helper_handlers;

	return &helper->std;
}