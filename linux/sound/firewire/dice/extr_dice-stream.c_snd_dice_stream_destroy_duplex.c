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
struct snd_dice {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDTP_IN_STREAM ; 
 int /*<<< orphan*/  AMDTP_OUT_STREAM ; 
 unsigned int MAX_STREAMS ; 
 int /*<<< orphan*/  amdtp_domain_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_dice*,int /*<<< orphan*/ ,unsigned int) ; 

void snd_dice_stream_destroy_duplex(struct snd_dice *dice)
{
	unsigned int i;

	for (i = 0; i < MAX_STREAMS; i++) {
		destroy_stream(dice, AMDTP_IN_STREAM, i);
		destroy_stream(dice, AMDTP_OUT_STREAM, i);
	}

	amdtp_domain_destroy(&dice->domain);
}