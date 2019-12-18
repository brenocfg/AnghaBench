#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct hpi_response {int dummy; } ;
struct hpi_message {int /*<<< orphan*/  function; void* obj_index; void* adapter_index; } ;
struct TYPE_4__ {void* h_owner; scalar_t__ open_flag; } ;
struct TYPE_3__ {void* h_owner; scalar_t__ open_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 void* HPIMSGX_ALLADAPTERS ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  HPI_ISTREAM_GROUP_RESET ; 
 int /*<<< orphan*/  HPI_ISTREAM_HOSTBUFFER_FREE ; 
 int /*<<< orphan*/  HPI_ISTREAM_RESET ; 
 int HPI_MAX_ADAPTERS ; 
 int HPI_MAX_STREAMS ; 
 int /*<<< orphan*/  HPI_OBJ_ISTREAM ; 
 int /*<<< orphan*/  HPI_OBJ_OSTREAM ; 
 int /*<<< orphan*/  HPI_OSTREAM_GROUP_RESET ; 
 int /*<<< orphan*/  HPI_OSTREAM_HOSTBUFFER_FREE ; 
 int /*<<< orphan*/  HPI_OSTREAM_RESET ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_entry_point (struct hpi_message*,struct hpi_response*) ; 
 TYPE_2__** instream_user_open ; 
 TYPE_1__** outstream_user_open ; 

__attribute__((used)) static void HPIMSGX__cleanup(u16 adapter_index, void *h_owner)
{
	int i, adapter, adapter_limit;

	if (!h_owner)
		return;

	if (adapter_index == HPIMSGX_ALLADAPTERS) {
		adapter = 0;
		adapter_limit = HPI_MAX_ADAPTERS;
	} else {
		adapter = adapter_index;
		adapter_limit = adapter + 1;
	}

	for (; adapter < adapter_limit; adapter++) {
		/*      printk(KERN_INFO "Cleanup adapter #%d\n",wAdapter); */
		for (i = 0; i < HPI_MAX_STREAMS; i++) {
			if (h_owner ==
				outstream_user_open[adapter][i].h_owner) {
				struct hpi_message hm;
				struct hpi_response hr;

				HPI_DEBUG_LOG(DEBUG,
					"Close adapter %d ostream %d\n",
					adapter, i);

				hpi_init_message_response(&hm, &hr,
					HPI_OBJ_OSTREAM, HPI_OSTREAM_RESET);
				hm.adapter_index = (u16)adapter;
				hm.obj_index = (u16)i;
				hw_entry_point(&hm, &hr);

				hm.function = HPI_OSTREAM_HOSTBUFFER_FREE;
				hw_entry_point(&hm, &hr);

				hm.function = HPI_OSTREAM_GROUP_RESET;
				hw_entry_point(&hm, &hr);

				outstream_user_open[adapter][i].open_flag = 0;
				outstream_user_open[adapter][i].h_owner =
					NULL;
			}
			if (h_owner == instream_user_open[adapter][i].h_owner) {
				struct hpi_message hm;
				struct hpi_response hr;

				HPI_DEBUG_LOG(DEBUG,
					"Close adapter %d istream %d\n",
					adapter, i);

				hpi_init_message_response(&hm, &hr,
					HPI_OBJ_ISTREAM, HPI_ISTREAM_RESET);
				hm.adapter_index = (u16)adapter;
				hm.obj_index = (u16)i;
				hw_entry_point(&hm, &hr);

				hm.function = HPI_ISTREAM_HOSTBUFFER_FREE;
				hw_entry_point(&hm, &hr);

				hm.function = HPI_ISTREAM_GROUP_RESET;
				hw_entry_point(&hm, &hr);

				instream_user_open[adapter][i].open_flag = 0;
				instream_user_open[adapter][i].h_owner = NULL;
			}
		}
	}
}