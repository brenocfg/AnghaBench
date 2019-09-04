#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * utrans; } ;
typedef  TYPE_1__ Transliterator_object ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_P (TYPE_1__*) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utrans_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void transliterator_object_destroy( Transliterator_object* to )
{
	if( !to )
		return;

	if( to->utrans )
	{
		utrans_close( to->utrans );
		to->utrans = NULL;
	}

	intl_error_reset( TRANSLITERATOR_ERROR_P( to ) );
}