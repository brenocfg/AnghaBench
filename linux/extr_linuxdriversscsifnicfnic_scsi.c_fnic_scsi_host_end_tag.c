#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_3__* request; } ;
struct fnic {TYPE_2__* lport; } ;
struct blk_queue_tag {int /*<<< orphan*/  tag_map; int /*<<< orphan*/ ** tag_index; } ;
struct TYPE_6__ {int tag; } ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {struct blk_queue_tag* bqt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SCSI_NO_TAG ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fnic_scsi_host_end_tag(struct fnic *fnic, struct scsi_cmnd *sc)
{
	struct blk_queue_tag *bqt = fnic->lport->host->bqt;
	int tag = sc->request->tag;

	if (tag == SCSI_NO_TAG)
		return;

	BUG_ON(!bqt || !bqt->tag_index[tag]);
	if (!bqt)
		return;

	bqt->tag_index[tag] = NULL;
	clear_bit(tag, bqt->tag_map);

	return;
}