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
struct ima_event_data {scalar_t__ buf_len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FMT_HEX ; 
 int ima_write_template_field_data (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct ima_field_data*) ; 

int ima_eventbuf_init(struct ima_event_data *event_data,
		      struct ima_field_data *field_data)
{
	if ((!event_data->buf) || (event_data->buf_len == 0))
		return 0;

	return ima_write_template_field_data(event_data->buf,
					     event_data->buf_len, DATA_FMT_HEX,
					     field_data);
}