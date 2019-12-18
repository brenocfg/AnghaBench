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
typedef  int /*<<< orphan*/  msgformat_data ;

/* Variables and functions */
 int /*<<< orphan*/ * ecalloc (int,int) ; 
 int /*<<< orphan*/  msgformat_data_init (int /*<<< orphan*/ *) ; 

msgformat_data* msgformat_data_create( void )
{
	msgformat_data* mf_data = ecalloc( 1, sizeof(msgformat_data) );

	msgformat_data_init( mf_data );

	return mf_data;
}