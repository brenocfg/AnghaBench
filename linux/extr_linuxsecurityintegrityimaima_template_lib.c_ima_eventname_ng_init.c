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
struct ima_event_data {int dummy; } ;

/* Variables and functions */
 int ima_eventname_init_common (struct ima_event_data*,struct ima_field_data*,int) ; 

int ima_eventname_ng_init(struct ima_event_data *event_data,
			  struct ima_field_data *field_data)
{
	return ima_eventname_init_common(event_data, field_data, false);
}