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
struct snd_pcm_substream {int /*<<< orphan*/  number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_card_asihpi_pcm* private_data; } ;
struct snd_card_asihpi_pcm {scalar_t__ pcm_buf_elapsed_dma_ofs; scalar_t__ pcm_buf_dma_ofs; scalar_t__ pcm_buf_host_rw_ofs; int /*<<< orphan*/  h_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_instream_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_card_asihpi_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_card_asihpi_pcm *dpcm = runtime->private_data;

	hpi_handle_error(hpi_instream_reset(dpcm->h_stream));
	dpcm->pcm_buf_host_rw_ofs = 0;
	dpcm->pcm_buf_dma_ofs = 0;
	dpcm->pcm_buf_elapsed_dma_ofs = 0;

	snd_printdd("Capture Prepare %d\n", substream->number);
	return 0;
}