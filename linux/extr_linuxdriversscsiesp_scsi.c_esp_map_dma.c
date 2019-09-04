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
struct scsi_cmnd {int sc_data_direction; } ;
struct scatterlist {int dummy; } ;
struct TYPE_4__ {int num_sg; } ;
struct esp_cmd_priv {int tot_residue; TYPE_2__ u; struct scatterlist* cur_sg; scalar_t__ cur_residue; } ;
struct esp {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* map_sg ) (struct esp*,struct scatterlist*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int DMA_NONE ; 
 struct esp_cmd_priv* ESP_CMD_PRIV (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 int stub1 (struct esp*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void esp_map_dma(struct esp *esp, struct scsi_cmnd *cmd)
{
	struct esp_cmd_priv *spriv = ESP_CMD_PRIV(cmd);
	struct scatterlist *sg = scsi_sglist(cmd);
	int dir = cmd->sc_data_direction;
	int total, i;

	if (dir == DMA_NONE)
		return;

	spriv->u.num_sg = esp->ops->map_sg(esp, sg, scsi_sg_count(cmd), dir);
	spriv->cur_residue = sg_dma_len(sg);
	spriv->cur_sg = sg;

	total = 0;
	for (i = 0; i < spriv->u.num_sg; i++)
		total += sg_dma_len(&sg[i]);
	spriv->tot_residue = total;
}