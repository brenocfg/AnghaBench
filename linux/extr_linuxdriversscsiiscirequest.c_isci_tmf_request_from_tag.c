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
typedef  int /*<<< orphan*/  u16 ;
struct isci_tmf {int dummy; } ;
struct TYPE_2__ {struct isci_tmf* tmf_task_ptr; } ;
struct isci_request {int /*<<< orphan*/  flags; TYPE_1__ ttype_ptr; } ;
struct isci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IREQ_TMF ; 
 struct isci_request* isci_request_from_tag (struct isci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct isci_request *isci_tmf_request_from_tag(struct isci_host *ihost,
					       struct isci_tmf *isci_tmf,
					       u16 tag)
{
	struct isci_request *ireq;

	ireq = isci_request_from_tag(ihost, tag);
	ireq->ttype_ptr.tmf_task_ptr = isci_tmf;
	set_bit(IREQ_TMF, &ireq->flags);

	return ireq;
}