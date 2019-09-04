#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hpi_response {scalar_t__ error; } ;
struct hpi_message {size_t adapter_index; size_t obj_index; } ;
struct TYPE_2__ {void* h_owner; scalar_t__ open_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,void*,size_t,size_t,void*) ; 
 scalar_t__ HPI_ERROR_OBJ_NOT_OPEN ; 
 int /*<<< orphan*/  HPI_OBJ_OSTREAM ; 
 int /*<<< orphan*/  HPI_OSTREAM_CLOSE ; 
 int /*<<< orphan*/  HPI_OSTREAM_RESET ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  hpi_init_message_response (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpios_msgxlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hpios_msgxlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_entry_point (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  msgx_lock ; 
 TYPE_1__** outstream_user_open ; 

__attribute__((used)) static void outstream_close(struct hpi_message *phm, struct hpi_response *phr,
	void *h_owner)
{

	struct hpi_message hm;
	struct hpi_response hr;

	hpi_init_response(phr, HPI_OBJ_OSTREAM, HPI_OSTREAM_CLOSE, 0);

	hpios_msgxlock_lock(&msgx_lock);

	if (h_owner ==
		outstream_user_open[phm->adapter_index][phm->
			obj_index].h_owner) {
		/* HPI_DEBUG_LOG(INFO,"closing adapter %d "
		   "outstream %d owned by %p\n",
		   phm->wAdapterIndex, phm->wObjIndex, hOwner); */
		outstream_user_open[phm->adapter_index][phm->
			obj_index].h_owner = NULL;
		hpios_msgxlock_unlock(&msgx_lock);
		/* issue a reset */
		hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_RESET);
		hm.adapter_index = phm->adapter_index;
		hm.obj_index = phm->obj_index;
		hw_entry_point(&hm, &hr);
		hpios_msgxlock_lock(&msgx_lock);
		if (hr.error) {
			outstream_user_open[phm->adapter_index][phm->
				obj_index].h_owner = h_owner;
			phr->error = hr.error;
		} else {
			outstream_user_open[phm->adapter_index][phm->
				obj_index].open_flag = 0;
			outstream_user_open[phm->adapter_index][phm->
				obj_index].h_owner = NULL;
		}
	} else {
		HPI_DEBUG_LOG(WARNING,
			"%p trying to close %d outstream %d owned by %p\n",
			h_owner, phm->adapter_index, phm->obj_index,
			outstream_user_open[phm->adapter_index][phm->
				obj_index].h_owner);
		phr->error = HPI_ERROR_OBJ_NOT_OPEN;
	}
	hpios_msgxlock_unlock(&msgx_lock);
}