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
struct TYPE_3__ {int /*<<< orphan*/  error; int /*<<< orphan*/ * umsgf; int /*<<< orphan*/ * arg_types; int /*<<< orphan*/ * orig_format; } ;
typedef  TYPE_1__ msgformat_data ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_error_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umsg_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

void msgformat_data_free(msgformat_data* mf_data)
{
	if (!mf_data)
		return;

	if (mf_data->umsgf)
		umsg_close(mf_data->umsgf);

	if (mf_data->orig_format) {
		efree(mf_data->orig_format);
		mf_data->orig_format = NULL;
	}

	if (mf_data->arg_types) {
		zend_hash_destroy(mf_data->arg_types);
		efree(mf_data->arg_types);
		mf_data->arg_types = NULL;
	}

	mf_data->umsgf = NULL;
	intl_error_reset(&mf_data->error);
}