#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  error; scalar_t__ tz_set; int /*<<< orphan*/ * arg_types; int /*<<< orphan*/ * orig_format; int /*<<< orphan*/ * umsgf; } ;
typedef  TYPE_1__ msgformat_data ;

/* Variables and functions */
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ *) ; 

void msgformat_data_init( msgformat_data* mf_data )
{
	if( !mf_data )
		return;

	mf_data->umsgf			= NULL;
	mf_data->orig_format	= NULL;
	mf_data->arg_types		= NULL;
	mf_data->tz_set			= 0;
	intl_error_reset( &mf_data->error );
}