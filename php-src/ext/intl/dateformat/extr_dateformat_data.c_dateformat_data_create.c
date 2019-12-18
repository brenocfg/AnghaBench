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
typedef  int /*<<< orphan*/  dateformat_data ;

/* Variables and functions */
 int /*<<< orphan*/  dateformat_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecalloc (int,int) ; 

dateformat_data* dateformat_data_create( void )
{
	dateformat_data* datef_data = ecalloc( 1, sizeof(dateformat_data) );

	dateformat_data_init( datef_data );

	return datef_data;
}