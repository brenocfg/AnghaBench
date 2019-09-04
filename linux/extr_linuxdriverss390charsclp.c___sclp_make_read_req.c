#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sclp_req {int dummy; } ;
struct sccb_header {int* control_mask; scalar_t__ function_code; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {struct sccb_header* sccb; int /*<<< orphan*/  callback; scalar_t__ start_count; int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SCLP_CMDW_READ_EVENT_DATA ; 
 int /*<<< orphan*/  SCLP_REQ_QUEUED ; 
 int /*<<< orphan*/  clear_page (struct sccb_header*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sclp_read_cb ; 
 TYPE_1__ sclp_read_req ; 
 scalar_t__ sclp_read_sccb ; 

__attribute__((used)) static void __sclp_make_read_req(void)
{
	struct sccb_header *sccb;

	sccb = (struct sccb_header *) sclp_read_sccb;
	clear_page(sccb);
	memset(&sclp_read_req, 0, sizeof(struct sclp_req));
	sclp_read_req.command = SCLP_CMDW_READ_EVENT_DATA;
	sclp_read_req.status = SCLP_REQ_QUEUED;
	sclp_read_req.start_count = 0;
	sclp_read_req.callback = sclp_read_cb;
	sclp_read_req.sccb = sccb;
	sccb->length = PAGE_SIZE;
	sccb->function_code = 0;
	sccb->control_mask[2] = 0x80;
}