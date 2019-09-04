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
typedef  scalar_t__ u32 ;
struct fsi_stream {int /*<<< orphan*/  chan; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_RST ; 
 scalar_t__ CRA ; 
 scalar_t__ CRB ; 
 scalar_t__ DMA_ON ; 
 int /*<<< orphan*/  OUT_DMAC ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 scalar_t__ fsi_is_clk_master (struct fsi_priv*) ; 
 scalar_t__ fsi_is_port_a (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_master_mask_set (struct fsi_master*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fsi_reg_mask_set (struct fsi_priv*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int fsi_dma_push_start_stop(struct fsi_priv *fsi, struct fsi_stream *io,
				 int start)
{
	struct fsi_master *master = fsi_get_master(fsi);
	u32 clk  = fsi_is_port_a(fsi) ? CRA  : CRB;
	u32 enable = start ? DMA_ON : 0;

	fsi_reg_mask_set(fsi, OUT_DMAC, DMA_ON, enable);

	dmaengine_terminate_all(io->chan);

	if (fsi_is_clk_master(fsi))
		fsi_master_mask_set(master, CLK_RST, clk, (enable) ? clk : 0);

	return 0;
}