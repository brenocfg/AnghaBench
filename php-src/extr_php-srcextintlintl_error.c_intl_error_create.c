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
typedef  int /*<<< orphan*/  intl_error ;

/* Variables and functions */
 int /*<<< orphan*/ * ecalloc (int,int) ; 
 int /*<<< orphan*/  intl_error_init (int /*<<< orphan*/ *) ; 

intl_error* intl_error_create( void )
{
	intl_error* err = ecalloc( 1, sizeof( intl_error ) );

	intl_error_init( err );

	return err;
}