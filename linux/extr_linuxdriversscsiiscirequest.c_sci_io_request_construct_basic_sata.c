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
struct sas_task {scalar_t__ data_dir; int /*<<< orphan*/  total_xfer_len; } ;
struct isci_request {int /*<<< orphan*/  sm; int /*<<< orphan*/  protocol; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 scalar_t__ DMA_NONE ; 
 int /*<<< orphan*/  SAS_PROTOCOL_STP ; 
 int /*<<< orphan*/  SCI_REQ_CONSTRUCTED ; 
 int SCI_SUCCESS ; 
 struct sas_task* isci_request_access_task (struct isci_request*) ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sci_io_request_construct_sata (struct isci_request*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static enum sci_status sci_io_request_construct_basic_sata(struct isci_request *ireq)
{
	enum sci_status status;
	bool copy = false;
	struct sas_task *task = isci_request_access_task(ireq);

	ireq->protocol = SAS_PROTOCOL_STP;

	copy = (task->data_dir == DMA_NONE) ? false : true;

	status = sci_io_request_construct_sata(ireq,
						task->total_xfer_len,
						task->data_dir,
						copy);

	if (status == SCI_SUCCESS)
		sci_change_state(&ireq->sm, SCI_REQ_CONSTRUCTED);

	return status;
}