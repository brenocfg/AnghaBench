#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int req_prod_pvt; } ;
struct pvcalls_bedata {TYPE_1__* rsp; TYPE_2__ ring; } ;
struct TYPE_4__ {scalar_t__ req_id; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ PVCALLS_INVALID_ID ; 
 scalar_t__ RING_FULL (TYPE_2__*) ; 
 int RING_SIZE (TYPE_2__*) ; 

__attribute__((used)) static inline int get_request(struct pvcalls_bedata *bedata, int *req_id)
{
	*req_id = bedata->ring.req_prod_pvt & (RING_SIZE(&bedata->ring) - 1);
	if (RING_FULL(&bedata->ring) ||
	    bedata->rsp[*req_id].req_id != PVCALLS_INVALID_ID)
		return -EAGAIN;
	return 0;
}