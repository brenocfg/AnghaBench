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
struct zfcp_qdio {int /*<<< orphan*/  res_q; int /*<<< orphan*/  req_q; TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ ccw_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  kfree (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  qdio_free (scalar_t__) ; 
 int /*<<< orphan*/  qdio_free_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfcp_qdio_destroy(struct zfcp_qdio *qdio)
{
	if (!qdio)
		return;

	if (qdio->adapter->ccw_device)
		qdio_free(qdio->adapter->ccw_device);

	qdio_free_buffers(qdio->req_q, QDIO_MAX_BUFFERS_PER_Q);
	qdio_free_buffers(qdio->res_q, QDIO_MAX_BUFFERS_PER_Q);
	kfree(qdio);
}