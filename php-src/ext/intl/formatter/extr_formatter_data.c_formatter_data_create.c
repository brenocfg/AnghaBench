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
typedef  int /*<<< orphan*/  formatter_data ;

/* Variables and functions */
 int /*<<< orphan*/ * ecalloc (int,int) ; 
 int /*<<< orphan*/  formatter_data_init (int /*<<< orphan*/ *) ; 

formatter_data* formatter_data_create( void )
{
	formatter_data* nf_data = ecalloc( 1, sizeof(formatter_data) );

	formatter_data_init( nf_data );

	return nf_data;
}