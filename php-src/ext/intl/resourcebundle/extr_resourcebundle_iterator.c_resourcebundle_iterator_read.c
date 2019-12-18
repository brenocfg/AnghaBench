#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UErrorCode ;
struct TYPE_6__ {int /*<<< orphan*/  current; int /*<<< orphan*/  currentkey; scalar_t__ is_table; int /*<<< orphan*/  i; TYPE_1__* subject; } ;
struct TYPE_5__ {int /*<<< orphan*/  child; int /*<<< orphan*/  me; } ;
typedef  TYPE_1__ ResourceBundle_object ;
typedef  TYPE_2__ ResourceBundle_iterator ;

/* Variables and functions */
 scalar_t__ U_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  estrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resourcebundle_extract_value (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ures_getByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ures_getKey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resourcebundle_iterator_read( ResourceBundle_iterator *iterator )
{
	UErrorCode icuerror = U_ZERO_ERROR;
	ResourceBundle_object *rb = iterator->subject;

	rb->child = ures_getByIndex( rb->me, iterator->i, rb->child, &icuerror );

	if (U_SUCCESS(icuerror)) {
		/* ATTN: key extraction must be the first thing to do... rb->child might be reset in read! */
		if (iterator->is_table) {
			iterator->currentkey = estrdup( ures_getKey( rb->child ) );
		}
		resourcebundle_extract_value( &iterator->current, rb );
	}
	else {
		// zend_throw_exception( spl_ce_OutOfRangeException, "Running past end of ResourceBundle", 0);
		ZVAL_UNDEF(&iterator->current);
	}
}