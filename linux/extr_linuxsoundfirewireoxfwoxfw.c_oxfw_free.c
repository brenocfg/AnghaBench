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
struct snd_oxfw {int /*<<< orphan*/  mutex; struct snd_oxfw* spec; struct snd_oxfw** rx_stream_formats; struct snd_oxfw** tx_stream_formats; int /*<<< orphan*/  unit; int /*<<< orphan*/  tx_stream; scalar_t__ has_output; int /*<<< orphan*/  rx_stream; } ;

/* Variables and functions */
 unsigned int SND_OXFW_STREAM_FORMAT_ENTRIES ; 
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_oxfw*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_oxfw_stream_destroy_simplex (struct snd_oxfw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oxfw_free(struct snd_oxfw *oxfw)
{
	unsigned int i;

	snd_oxfw_stream_destroy_simplex(oxfw, &oxfw->rx_stream);
	if (oxfw->has_output)
		snd_oxfw_stream_destroy_simplex(oxfw, &oxfw->tx_stream);

	fw_unit_put(oxfw->unit);

	for (i = 0; i < SND_OXFW_STREAM_FORMAT_ENTRIES; i++) {
		kfree(oxfw->tx_stream_formats[i]);
		kfree(oxfw->rx_stream_formats[i]);
	}

	kfree(oxfw->spec);
	mutex_destroy(&oxfw->mutex);
	kfree(oxfw);
}