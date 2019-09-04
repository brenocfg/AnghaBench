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
struct snd_pcm_substream {int dummy; } ;
struct fsi_stream {int /*<<< orphan*/  buff_sample_pos; } ;
struct fsi_priv {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 struct fsi_priv* fsi_get_priv (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  fsi_sample2frame (struct fsi_priv*,int /*<<< orphan*/ ) ; 
 struct fsi_stream* fsi_stream_get (struct fsi_priv*,struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t fsi_pointer(struct snd_pcm_substream *substream)
{
	struct fsi_priv *fsi = fsi_get_priv(substream);
	struct fsi_stream *io = fsi_stream_get(fsi, substream);

	return fsi_sample2frame(fsi, io->buff_sample_pos);
}