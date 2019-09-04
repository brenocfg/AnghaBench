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
struct fsl_asrc_pair {int index; struct fsl_asrc* asrc_priv; } ;
struct fsl_asrc {TYPE_1__* pdev; } ;
struct dma_chan {int dummy; } ;
typedef  enum asrc_pair_index { ____Placeholder_asrc_pair_index } asrc_pair_index ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IN ; 
 struct dma_chan* dma_request_slave_channel (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,int) ; 

struct dma_chan *fsl_asrc_get_dma_channel(struct fsl_asrc_pair *pair, bool dir)
{
	struct fsl_asrc *asrc_priv = pair->asrc_priv;
	enum asrc_pair_index index = pair->index;
	char name[4];

	sprintf(name, "%cx%c", dir == IN ? 'r' : 't', index + 'a');

	return dma_request_slave_channel(&asrc_priv->pdev->dev, name);
}