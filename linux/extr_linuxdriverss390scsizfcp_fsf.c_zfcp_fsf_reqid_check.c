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
struct zfcp_qdio {struct qdio_buffer** res_q; struct zfcp_adapter* adapter; } ;
struct zfcp_fsf_req {int dummy; } ;
struct zfcp_adapter {TYPE_1__* ccw_device; int /*<<< orphan*/  req_list; } ;
struct qdio_buffer_element {int eflags; scalar_t__ addr; } ;
struct qdio_buffer {struct qdio_buffer_element* element; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QDIO_MAX_ELEMENTS_PER_BUFFER ; 
 int SBAL_EFLAGS_LAST_ENTRY ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  panic (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_complete (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_qdio_siosl (struct zfcp_adapter*) ; 
 struct zfcp_fsf_req* zfcp_reqlist_find_rm (int /*<<< orphan*/ ,unsigned long) ; 

void zfcp_fsf_reqid_check(struct zfcp_qdio *qdio, int sbal_idx)
{
	struct zfcp_adapter *adapter = qdio->adapter;
	struct qdio_buffer *sbal = qdio->res_q[sbal_idx];
	struct qdio_buffer_element *sbale;
	struct zfcp_fsf_req *fsf_req;
	unsigned long req_id;
	int idx;

	for (idx = 0; idx < QDIO_MAX_ELEMENTS_PER_BUFFER; idx++) {

		sbale = &sbal->element[idx];
		req_id = (unsigned long) sbale->addr;
		fsf_req = zfcp_reqlist_find_rm(adapter->req_list, req_id);

		if (!fsf_req) {
			/*
			 * Unknown request means that we have potentially memory
			 * corruption and must stop the machine immediately.
			 */
			zfcp_qdio_siosl(adapter);
			panic("error: unknown req_id (%lx) on adapter %s.\n",
			      req_id, dev_name(&adapter->ccw_device->dev));
		}

		zfcp_fsf_req_complete(fsf_req);

		if (likely(sbale->eflags & SBAL_EFLAGS_LAST_ENTRY))
			break;
	}
}