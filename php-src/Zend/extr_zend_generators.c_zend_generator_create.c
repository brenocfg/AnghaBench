#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_10__ {int /*<<< orphan*/ * handlers; } ;
struct TYPE_7__ {TYPE_3__* root; } ;
struct TYPE_8__ {TYPE_1__ ptr; scalar_t__ children; int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {int largest_used_integer_key; TYPE_4__ std; TYPE_2__ node; int /*<<< orphan*/  values; int /*<<< orphan*/  retval; } ;
typedef  TYPE_3__ zend_generator ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 TYPE_3__* emalloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_generator_handlers ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *zend_generator_create(zend_class_entry *class_type) /* {{{ */
{
	zend_generator *generator;

	generator = emalloc(sizeof(zend_generator));
	memset(generator, 0, sizeof(zend_generator));

	/* The key will be incremented on first use, so it'll start at 0 */
	generator->largest_used_integer_key = -1;

	ZVAL_UNDEF(&generator->retval);
	ZVAL_UNDEF(&generator->values);

	/* By default we have a tree of only one node */
	generator->node.parent = NULL;
	generator->node.children = 0;
	generator->node.ptr.root = generator;

	zend_object_std_init(&generator->std, class_type);
	generator->std.handlers = &zend_generator_handlers;

	return (zend_object*)generator;
}