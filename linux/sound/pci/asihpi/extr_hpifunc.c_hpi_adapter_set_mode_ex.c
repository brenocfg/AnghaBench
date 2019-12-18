#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct hpi_response {void* error; } ;
struct TYPE_4__ {void* query_or_set; int /*<<< orphan*/  adapter_mode; } ;
struct TYPE_5__ {TYPE_1__ mode; } ;
struct TYPE_6__ {TYPE_2__ ax; } ;
struct hpi_message {TYPE_3__ u; void* adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_SET_MODE ; 
 int /*<<< orphan*/  HPI_OBJ_ADAPTER ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_adapter_set_mode_ex(u16 adapter_index, u32 adapter_mode,
	u16 query_or_set)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_SET_MODE);
	hm.adapter_index = adapter_index;
	hm.u.ax.mode.adapter_mode = adapter_mode;
	hm.u.ax.mode.query_or_set = query_or_set;
	hpi_send_recv(&hm, &hr);
	return hr.error;
}