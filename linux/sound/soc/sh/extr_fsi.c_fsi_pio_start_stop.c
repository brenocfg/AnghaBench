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
typedef  int /*<<< orphan*/  u32 ;
struct fsi_stream {int dummy; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_RST ; 
 int /*<<< orphan*/  CRA ; 
 int /*<<< orphan*/  CRB ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_irq_disable (struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  fsi_irq_enable (struct fsi_priv*,struct fsi_stream*) ; 
 scalar_t__ fsi_is_clk_master (struct fsi_priv*) ; 
 scalar_t__ fsi_is_port_a (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_master_mask_set (struct fsi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_pio_start_stop(struct fsi_priv *fsi, struct fsi_stream *io,
			       int enable)
{
	struct fsi_master *master = fsi_get_master(fsi);
	u32 clk  = fsi_is_port_a(fsi) ? CRA  : CRB;

	if (enable)
		fsi_irq_enable(fsi, io);
	else
		fsi_irq_disable(fsi, io);

	if (fsi_is_clk_master(fsi))
		fsi_master_mask_set(master, CLK_RST, clk, (enable) ? clk : 0);

	return 0;
}