#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_8__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int is_table; scalar_t__ i; int /*<<< orphan*/ * currentkey; int /*<<< orphan*/  current; int /*<<< orphan*/  length; TYPE_1__* subject; TYPE_3__ intern; } ;
struct TYPE_6__ {int /*<<< orphan*/  me; } ;
typedef  TYPE_1__ ResourceBundle_object ;
typedef  TYPE_2__ ResourceBundle_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ URES_TABLE ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_INTL_RESOURCEBUNDLE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* emalloc (int) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resourcebundle_iterator_funcs ; 
 int /*<<< orphan*/  ures_getSize (int /*<<< orphan*/ ) ; 
 scalar_t__ ures_getType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_iterator_init (TYPE_3__*) ; 

zend_object_iterator *resourcebundle_get_iterator( zend_class_entry *ce, zval *object, int byref )
{
	ResourceBundle_object   *rb = Z_INTL_RESOURCEBUNDLE_P(object );
	ResourceBundle_iterator *iterator = emalloc( sizeof( ResourceBundle_iterator ) );

	if (byref) {
	     php_error( E_ERROR, "ResourceBundle does not support writable iterators" );
	}

	zend_iterator_init(&iterator->intern);
	Z_ADDREF_P(object);
	ZVAL_OBJ(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &resourcebundle_iterator_funcs;

	iterator->subject = rb;

	/* The iterated rb can only be either URES_TABLE or URES_ARRAY
	 * All other types are returned as php primitives!
	 */
	iterator->is_table = (ures_getType( rb->me ) == URES_TABLE);
	iterator->length = ures_getSize( rb->me );

	ZVAL_UNDEF(&iterator->current);
	iterator->currentkey = NULL;
	iterator->i = 0;

	return (zend_object_iterator *) iterator;
}