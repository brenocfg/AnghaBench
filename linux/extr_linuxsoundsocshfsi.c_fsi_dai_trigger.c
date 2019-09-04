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
struct snd_pcm_substream {int dummy; } ;
struct fsi_stream {int dummy; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct fsi_priv* fsi_get_priv (struct snd_pcm_substream*) ; 
 int fsi_hw_shutdown (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 int fsi_hw_startup (struct fsi_priv*,struct fsi_stream*,int /*<<< orphan*/ ) ; 
 struct fsi_stream* fsi_stream_get (struct fsi_priv*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  fsi_stream_init (struct fsi_priv*,struct fsi_stream*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  fsi_stream_quit (struct fsi_priv*,struct fsi_stream*) ; 
 int fsi_stream_start (struct fsi_priv*,struct fsi_stream*) ; 
 int /*<<< orphan*/  fsi_stream_stop (struct fsi_priv*,struct fsi_stream*) ; 
 int fsi_stream_transfer (struct fsi_stream*) ; 

__attribute__((used)) static int fsi_dai_trigger(struct snd_pcm_substream *substream, int cmd,
			   struct snd_soc_dai *dai)
{
	struct fsi_priv *fsi = fsi_get_priv(substream);
	struct fsi_stream *io = fsi_stream_get(fsi, substream);
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		fsi_stream_init(fsi, io, substream);
		if (!ret)
			ret = fsi_hw_startup(fsi, io, dai->dev);
		if (!ret)
			ret = fsi_stream_start(fsi, io);
		if (!ret)
			ret = fsi_stream_transfer(io);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (!ret)
			ret = fsi_hw_shutdown(fsi, dai->dev);
		fsi_stream_stop(fsi, io);
		fsi_stream_quit(fsi, io);
		break;
	}

	return ret;
}