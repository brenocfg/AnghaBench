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
struct srp_direct_buf {int /*<<< orphan*/  len; } ;
struct scatterlist {int dummy; } ;
struct iu_entry {TYPE_2__* target; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_length; int /*<<< orphan*/  t_data_nents; struct scatterlist* t_data_sg; } ;
struct ibmvscsis_cmd {TYPE_1__ se_cmd; struct iu_entry* iue; } ;
typedef  int (* srp_rdma_t ) (struct ibmvscsis_cmd*,struct scatterlist*,int,struct srp_direct_buf*,int,int,int) ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,struct iu_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srp_direct_data(struct ibmvscsis_cmd *cmd, struct srp_direct_buf *md,
			   enum dma_data_direction dir, srp_rdma_t rdma_io,
			   int dma_map, int ext_desc)
{
	struct iu_entry *iue = NULL;
	struct scatterlist *sg = NULL;
	int err, nsg = 0, len;

	if (dma_map) {
		iue = cmd->iue;
		sg = cmd->se_cmd.t_data_sg;
		nsg = dma_map_sg(iue->target->dev, sg, cmd->se_cmd.t_data_nents,
				 DMA_BIDIRECTIONAL);
		if (!nsg) {
			pr_err("fail to map %p %d\n", iue,
			       cmd->se_cmd.t_data_nents);
			return 0;
		}
		len = min(cmd->se_cmd.data_length, be32_to_cpu(md->len));
	} else {
		len = be32_to_cpu(md->len);
	}

	err = rdma_io(cmd, sg, nsg, md, 1, dir, len);

	if (dma_map)
		dma_unmap_sg(iue->target->dev, sg, nsg, DMA_BIDIRECTIONAL);

	return err;
}