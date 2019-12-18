#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Transliterator_object ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSLITERATOR_ERROR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transliterator_object_init( Transliterator_object* to )
{
	if( !to )
		return;

	intl_error_init( TRANSLITERATOR_ERROR_P( to ) );
}