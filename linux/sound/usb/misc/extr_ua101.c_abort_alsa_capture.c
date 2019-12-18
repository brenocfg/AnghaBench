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
struct TYPE_2__ {int /*<<< orphan*/  substream; } ;
struct ua101 {TYPE_1__ capture; int /*<<< orphan*/  states; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALSA_CAPTURE_RUNNING ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void abort_alsa_capture(struct ua101 *ua)
{
	if (test_bit(ALSA_CAPTURE_RUNNING, &ua->states))
		snd_pcm_stop_xrun(ua->capture.substream);
}