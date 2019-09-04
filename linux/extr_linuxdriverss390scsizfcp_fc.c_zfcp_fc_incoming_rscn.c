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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct zfcp_fsf_req {int /*<<< orphan*/  adapter; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct fsf_status_read_buffer {TYPE_1__ payload; } ;
struct fc_els_rscn_page {unsigned int rscn_page_flags; } ;
struct fc_els_rscn {int /*<<< orphan*/  rscn_plen; } ;

/* Variables and functions */
 unsigned int ELS_RSCN_ADDR_FMT_MASK ; 
 int /*<<< orphan*/  FCH_EVT_RSCN ; 
 int /*<<< orphan*/  _zfcp_fc_incoming_rscn (struct zfcp_fsf_req*,int /*<<< orphan*/ ,struct fc_els_rscn_page*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_conditional_port_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_enqueue_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfcp_fc_rscn_range_mask ; 

__attribute__((used)) static void zfcp_fc_incoming_rscn(struct zfcp_fsf_req *fsf_req)
{
	struct fsf_status_read_buffer *status_buffer = (void *)fsf_req->data;
	struct fc_els_rscn *head;
	struct fc_els_rscn_page *page;
	u16 i;
	u16 no_entries;
	unsigned int afmt;

	head = (struct fc_els_rscn *) status_buffer->payload.data;
	page = (struct fc_els_rscn_page *) head;

	/* see FC-FS */
	no_entries = be16_to_cpu(head->rscn_plen) /
		sizeof(struct fc_els_rscn_page);

	for (i = 1; i < no_entries; i++) {
		/* skip head and start with 1st element */
		page++;
		afmt = page->rscn_page_flags & ELS_RSCN_ADDR_FMT_MASK;
		_zfcp_fc_incoming_rscn(fsf_req, zfcp_fc_rscn_range_mask[afmt],
				       page);
		zfcp_fc_enqueue_event(fsf_req->adapter, FCH_EVT_RSCN,
				      *(u32 *)page);
	}
	zfcp_fc_conditional_port_scan(fsf_req->adapter);
}