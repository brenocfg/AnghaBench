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
typedef  int /*<<< orphan*/  u32 ;
struct ima_field_data {int dummy; } ;
struct ima_event_data {int /*<<< orphan*/  modsig; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FMT_HEX ; 
 int ima_get_raw_modsig (int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 
 int ima_write_template_field_data (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ima_field_data*) ; 

int ima_eventmodsig_init(struct ima_event_data *event_data,
			 struct ima_field_data *field_data)
{
	const void *data;
	u32 data_len;
	int rc;

	if (!event_data->modsig)
		return 0;

	/*
	 * modsig is a runtime structure containing pointers. Get its raw data
	 * instead.
	 */
	rc = ima_get_raw_modsig(event_data->modsig, &data, &data_len);
	if (rc)
		return rc;

	return ima_write_template_field_data(data, data_len, DATA_FMT_HEX,
					     field_data);
}