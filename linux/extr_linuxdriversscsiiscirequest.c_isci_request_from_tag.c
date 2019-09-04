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
typedef  int /*<<< orphan*/  u16 ;
struct isci_request {scalar_t__ num_sg_entries; scalar_t__ flags; int /*<<< orphan*/ * io_request_completion; int /*<<< orphan*/  io_tag; } ;
struct isci_host {struct isci_request** reqs; } ;

/* Variables and functions */
 size_t ISCI_TAG_TCI (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct isci_request *isci_request_from_tag(struct isci_host *ihost, u16 tag)
{
	struct isci_request *ireq;

	ireq = ihost->reqs[ISCI_TAG_TCI(tag)];
	ireq->io_tag = tag;
	ireq->io_request_completion = NULL;
	ireq->flags = 0;
	ireq->num_sg_entries = 0;

	return ireq;
}