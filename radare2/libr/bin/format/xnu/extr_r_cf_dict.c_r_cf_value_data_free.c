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
struct TYPE_4__ {int /*<<< orphan*/ * value; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RCFValueData ;

/* Variables and functions */
 int /*<<< orphan*/  R_CF_INVALID ; 
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_cf_value_data_free(RCFValueData *data) {
	if (!data) {
		return;
	}

	data->type = R_CF_INVALID;
	if (data->value) {
		r_buf_free (data->value);
		data->value = NULL;
	}

	R_FREE (data);
}