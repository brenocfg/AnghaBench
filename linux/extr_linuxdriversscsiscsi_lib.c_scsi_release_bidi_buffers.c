#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_data_buffer {int /*<<< orphan*/  table; } ;
struct scsi_cmnd {TYPE_2__* request; } ;
struct TYPE_4__ {TYPE_1__* next_rq; } ;
struct TYPE_3__ {struct scsi_data_buffer* special; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct scsi_data_buffer*) ; 
 int /*<<< orphan*/  scsi_sdb_cache ; 
 int /*<<< orphan*/  sg_free_table_chained (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void scsi_release_bidi_buffers(struct scsi_cmnd *cmd)
{
	struct scsi_data_buffer *bidi_sdb = cmd->request->next_rq->special;

	sg_free_table_chained(&bidi_sdb->table, false);
	kmem_cache_free(scsi_sdb_cache, bidi_sdb);
	cmd->request->next_rq->special = NULL;
}