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
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct hpi_response {scalar_t__ error; } ;
struct hpi_message {void* obj_index; void* adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ISTREAM_OPEN ; 
 int /*<<< orphan*/  HPI_OBJ_ISTREAM ; 
 scalar_t__ hpi_indexes_to_handle (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_instream_open(u16 adapter_index, u16 instream_index, u32 *ph_instream)
{
	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_OPEN);
	hm.adapter_index = adapter_index;
	hm.obj_index = instream_index;

	hpi_send_recv(&hm, &hr);

	if (hr.error == 0)
		*ph_instream =
			hpi_indexes_to_handle(HPI_OBJ_ISTREAM, adapter_index,
			instream_index);
	else
		*ph_instream = 0;

	return hr.error;
}