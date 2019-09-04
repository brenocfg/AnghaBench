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
typedef  int u32 ;
struct fsi_stream {int /*<<< orphan*/  fifo_sample_capa; } ;
struct fsi_priv {int chan_num; } ;
struct fsi_master {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_CTL ; 
 int /*<<< orphan*/  DOFF_CTL ; 
 int /*<<< orphan*/  FIFO_CLR ; 
 int /*<<< orphan*/  FIFO_SZ ; 
 int FIFO_SZ_MASK ; 
 int /*<<< orphan*/  IRQ_HALF ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  fsi_frame2sample (struct fsi_priv*,int) ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int fsi_get_port_shift (struct fsi_priv*,struct fsi_stream*) ; 
 int fsi_master_read (struct fsi_master*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_reg_mask_set (struct fsi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsi_stream_is_play (struct fsi_priv*,struct fsi_stream*) ; 

__attribute__((used)) static void fsi_fifo_init(struct fsi_priv *fsi,
			  struct fsi_stream *io,
			  struct device *dev)
{
	struct fsi_master *master = fsi_get_master(fsi);
	int is_play = fsi_stream_is_play(fsi, io);
	u32 shift, i;
	int frame_capa;

	/* get on-chip RAM capacity */
	shift = fsi_master_read(master, FIFO_SZ);
	shift >>= fsi_get_port_shift(fsi, io);
	shift &= FIFO_SZ_MASK;
	frame_capa = 256 << shift;
	dev_dbg(dev, "fifo = %d words\n", frame_capa);

	/*
	 * The maximum number of sample data varies depending
	 * on the number of channels selected for the format.
	 *
	 * FIFOs are used in 4-channel units in 3-channel mode
	 * and in 8-channel units in 5- to 7-channel mode
	 * meaning that more FIFOs than the required size of DPRAM
	 * are used.
	 *
	 * ex) if 256 words of DP-RAM is connected
	 * 1 channel:  256 (256 x 1 = 256)
	 * 2 channels: 128 (128 x 2 = 256)
	 * 3 channels:  64 ( 64 x 3 = 192)
	 * 4 channels:  64 ( 64 x 4 = 256)
	 * 5 channels:  32 ( 32 x 5 = 160)
	 * 6 channels:  32 ( 32 x 6 = 192)
	 * 7 channels:  32 ( 32 x 7 = 224)
	 * 8 channels:  32 ( 32 x 8 = 256)
	 */
	for (i = 1; i < fsi->chan_num; i <<= 1)
		frame_capa >>= 1;
	dev_dbg(dev, "%d channel %d store\n",
		fsi->chan_num, frame_capa);

	io->fifo_sample_capa = fsi_frame2sample(fsi, frame_capa);

	/*
	 * set interrupt generation factor
	 * clear FIFO
	 */
	if (is_play) {
		fsi_reg_write(fsi,	DOFF_CTL, IRQ_HALF);
		fsi_reg_mask_set(fsi,	DOFF_CTL, FIFO_CLR, FIFO_CLR);
	} else {
		fsi_reg_write(fsi,	DIFF_CTL, IRQ_HALF);
		fsi_reg_mask_set(fsi,	DIFF_CTL, FIFO_CLR, FIFO_CLR);
	}
}