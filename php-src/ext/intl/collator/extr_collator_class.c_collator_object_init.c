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
typedef  int /*<<< orphan*/  Collator_object ;

/* Variables and functions */
 int /*<<< orphan*/  COLLATOR_ERROR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_init (int /*<<< orphan*/ ) ; 

void collator_object_init( Collator_object* co )
{
	if( !co )
		return;

	intl_error_init( COLLATOR_ERROR_P( co ) );
}