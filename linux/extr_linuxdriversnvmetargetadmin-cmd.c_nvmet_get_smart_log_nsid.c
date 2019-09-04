#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {TYPE_3__* cmd; TYPE_1__* sq; } ;
struct nvmet_ns {TYPE_4__* bdev; } ;
struct nvme_smart_log {int /*<<< orphan*/ * data_units_written; int /*<<< orphan*/ * host_writes; int /*<<< orphan*/ * data_units_read; int /*<<< orphan*/ * host_reads; } ;
struct TYPE_8__ {int /*<<< orphan*/  bd_part; } ;
struct TYPE_6__ {int /*<<< orphan*/  nsid; } ;
struct TYPE_7__ {TYPE_2__ get_log_page; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SC_INVALID_NS ; 
 int /*<<< orphan*/  NVME_SC_SUCCESS ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/ * ios ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct nvmet_ns* nvmet_find_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_put_namespace (struct nvmet_ns*) ; 
 int /*<<< orphan*/  part_stat_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sectors ; 

__attribute__((used)) static u16 nvmet_get_smart_log_nsid(struct nvmet_req *req,
		struct nvme_smart_log *slog)
{
	struct nvmet_ns *ns;
	u64 host_reads, host_writes, data_units_read, data_units_written;

	ns = nvmet_find_namespace(req->sq->ctrl, req->cmd->get_log_page.nsid);
	if (!ns) {
		pr_err("nvmet : Could not find namespace id : %d\n",
				le32_to_cpu(req->cmd->get_log_page.nsid));
		return NVME_SC_INVALID_NS;
	}

	/* we don't have the right data for file backed ns */
	if (!ns->bdev)
		goto out;

	host_reads = part_stat_read(ns->bdev->bd_part, ios[READ]);
	data_units_read = part_stat_read(ns->bdev->bd_part, sectors[READ]);
	host_writes = part_stat_read(ns->bdev->bd_part, ios[WRITE]);
	data_units_written = part_stat_read(ns->bdev->bd_part, sectors[WRITE]);

	put_unaligned_le64(host_reads, &slog->host_reads[0]);
	put_unaligned_le64(data_units_read, &slog->data_units_read[0]);
	put_unaligned_le64(host_writes, &slog->host_writes[0]);
	put_unaligned_le64(data_units_written, &slog->data_units_written[0]);
out:
	nvmet_put_namespace(ns);

	return NVME_SC_SUCCESS;
}