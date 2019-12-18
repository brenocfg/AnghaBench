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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct fsi_stream {int /*<<< orphan*/  uerr_num; int /*<<< orphan*/  oerr_num; scalar_t__ bus_option; scalar_t__ sample_width; scalar_t__ period_pos; scalar_t__ period_samples; scalar_t__ buff_sample_pos; scalar_t__ buff_sample_capa; int /*<<< orphan*/ * substream; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai* fsi_get_dai (int /*<<< orphan*/ *) ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_stream_handler_call (struct fsi_stream*,int /*<<< orphan*/ ,struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  quit ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fsi_stream_quit(struct fsi_priv *fsi, struct fsi_stream *io)
{
	struct snd_soc_dai *dai = fsi_get_dai(io->substream);
	struct fsi_master *master = fsi_get_master(fsi);
	unsigned long flags;

	spin_lock_irqsave(&master->lock, flags);

	if (io->oerr_num > 0)
		dev_err(dai->dev, "over_run = %d\n", io->oerr_num);

	if (io->uerr_num > 0)
		dev_err(dai->dev, "under_run = %d\n", io->uerr_num);

	fsi_stream_handler_call(io, quit, fsi, io);
	io->substream	= NULL;
	io->buff_sample_capa	= 0;
	io->buff_sample_pos	= 0;
	io->period_samples	= 0;
	io->period_pos		= 0;
	io->sample_width	= 0;
	io->bus_option		= 0;
	io->oerr_num	= 0;
	io->uerr_num	= 0;
	spin_unlock_irqrestore(&master->lock, flags);
}