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
struct snd_pcm_substream {struct isight* private_data; } ;
struct isight {int /*<<< orphan*/  unit; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  iso_packets_buffer_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isight_close(struct snd_pcm_substream *substream)
{
	struct isight *isight = substream->private_data;

	iso_packets_buffer_destroy(&isight->buffer, isight->unit);

	return 0;
}