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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  period_size; int /*<<< orphan*/  buffer_size; } ;
struct fsi_stream {int oerr_num; int uerr_num; scalar_t__ bus_option; int /*<<< orphan*/  sample_width; scalar_t__ period_pos; void* period_samples; scalar_t__ buff_sample_pos; void* buff_sample_capa; struct snd_pcm_substream* substream; } ;
struct fsi_priv {int dummy; } ;
struct fsi_master {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 void* fsi_frame2sample (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_stream_handler_call (struct fsi_stream*,int /*<<< orphan*/ ,struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  samples_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fsi_stream_init(struct fsi_priv *fsi,
			    struct fsi_stream *io,
			    struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct fsi_master *master = fsi_get_master(fsi);
	unsigned long flags;

	spin_lock_irqsave(&master->lock, flags);
	io->substream	= substream;
	io->buff_sample_capa	= fsi_frame2sample(fsi, runtime->buffer_size);
	io->buff_sample_pos	= 0;
	io->period_samples	= fsi_frame2sample(fsi, runtime->period_size);
	io->period_pos		= 0;
	io->sample_width	= samples_to_bytes(runtime, 1);
	io->bus_option		= 0;
	io->oerr_num	= -1; /* ignore 1st err */
	io->uerr_num	= -1; /* ignore 1st err */
	fsi_stream_handler_call(io, init, fsi, io);
	spin_unlock_irqrestore(&master->lock, flags);
}