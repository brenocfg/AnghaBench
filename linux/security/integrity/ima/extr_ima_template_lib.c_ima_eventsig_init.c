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
struct ima_field_data {int dummy; } ;
struct ima_event_data {int /*<<< orphan*/  xattr_len; struct evm_ima_xattr_data* xattr_value; } ;
struct evm_ima_xattr_data {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FMT_HEX ; 
 scalar_t__ EVM_IMA_XATTR_DIGSIG ; 
 int ima_write_template_field_data (struct evm_ima_xattr_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ima_field_data*) ; 

int ima_eventsig_init(struct ima_event_data *event_data,
		      struct ima_field_data *field_data)
{
	struct evm_ima_xattr_data *xattr_value = event_data->xattr_value;

	if ((!xattr_value) || (xattr_value->type != EVM_IMA_XATTR_DIGSIG))
		return 0;

	return ima_write_template_field_data(xattr_value, event_data->xattr_len,
					     DATA_FMT_HEX, field_data);
}