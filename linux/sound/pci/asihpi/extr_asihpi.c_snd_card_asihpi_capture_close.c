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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_card_asihpi_pcm {int /*<<< orphan*/  h_stream; } ;
struct TYPE_2__ {struct snd_card_asihpi_pcm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_instream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_card_asihpi_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_card_asihpi_pcm *dpcm = substream->runtime->private_data;

	hpi_handle_error(hpi_instream_close(dpcm->h_stream));
	return 0;
}