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
struct snd_info_buffer {int dummy; } ;
struct loopback_cable {int /*<<< orphan*/ * streams; int /*<<< orphan*/  pause; int /*<<< orphan*/  running; int /*<<< orphan*/  valid; } ;
struct loopback {struct loopback_cable*** cables; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_dpcm_info (struct snd_info_buffer*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void print_substream_info(struct snd_info_buffer *buffer,
				 struct loopback *loopback,
				 int sub,
				 int num)
{
	struct loopback_cable *cable = loopback->cables[sub][num];

	snd_iprintf(buffer, "Cable %i substream %i:\n", num, sub);
	if (cable == NULL) {
		snd_iprintf(buffer, "  inactive\n");
		return;
	}
	snd_iprintf(buffer, "  valid: %u\n", cable->valid);
	snd_iprintf(buffer, "  running: %u\n", cable->running);
	snd_iprintf(buffer, "  pause: %u\n", cable->pause);
	print_dpcm_info(buffer, cable->streams[0], "Playback");
	print_dpcm_info(buffer, cable->streams[1], "Capture");
}