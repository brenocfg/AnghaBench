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
typedef  scalar_t__ u16 ;
struct hpi_response {scalar_t__ error; } ;
struct hpi_message {scalar_t__ adapter_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_MIXER_OPEN ; 
 int /*<<< orphan*/  HPI_OBJ_MIXER ; 
 scalar_t__ hpi_indexes_to_handle (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

u16 hpi_mixer_open(u16 adapter_index, u32 *ph_mixer)
{
	struct hpi_message hm;
	struct hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER, HPI_MIXER_OPEN);
	hm.adapter_index = adapter_index;

	hpi_send_recv(&hm, &hr);

	if (hr.error == 0)
		*ph_mixer =
			hpi_indexes_to_handle(HPI_OBJ_MIXER, adapter_index,
			0);
	else
		*ph_mixer = 0;
	return hr.error;
}