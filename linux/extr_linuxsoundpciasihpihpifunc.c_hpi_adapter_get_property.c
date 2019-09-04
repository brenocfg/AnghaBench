#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct TYPE_8__ {void* parameter2; void* parameter1; } ;
struct TYPE_9__ {TYPE_2__ property_get; } ;
struct TYPE_10__ {TYPE_3__ ax; } ;
struct hpi_response {void* error; TYPE_4__ u; } ;
struct TYPE_11__ {void* property; } ;
struct TYPE_12__ {TYPE_5__ property_set; } ;
struct TYPE_7__ {TYPE_6__ ax; } ;
struct hpi_message {TYPE_1__ u; void* adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_GET_PROPERTY ; 
 int /*<<< orphan*/  HPI_OBJ_ADAPTER ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_adapter_get_property(u16 adapter_index, u16 property,
	u16 *pw_parameter1, u16 *pw_parameter2)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_PROPERTY);
	hm.adapter_index = adapter_index;
	hm.u.ax.property_set.property = property;

	hpi_send_recv(&hm, &hr);
	if (!hr.error) {
		if (pw_parameter1)
			*pw_parameter1 = hr.u.ax.property_get.parameter1;
		if (pw_parameter2)
			*pw_parameter2 = hr.u.ax.property_get.parameter2;
	}

	return hr.error;
}