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
 int MAX_STREAMS ; 
 int amdtp_domain_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_stream (struct snd_dice*,int /*<<< orphan*/ ,int) ; 
 int init_stream (struct snd_dice*,int /*<<< orphan*/ ,int) ; 

int snd_dice_stream_init_duplex(struct snd_dice *dice)
{
	int i, err;

	for (i = 0; i < MAX_STREAMS; i++) {
		err = init_stream(dice, AMDTP_IN_STREAM, i);
		if (err < 0) {
			for (; i >= 0; i--)
				destroy_stream(dice, AMDTP_IN_STREAM, i);
			goto end;
		}
	}

	for (i = 0; i < MAX_STREAMS; i++) {
		err = init_stream(dice, AMDTP_OUT_STREAM, i);
		if (err < 0) {
			for (; i >= 0; i--)
				destroy_stream(dice, AMDTP_OUT_STREAM, i);
			for (i = 0; i < MAX_STREAMS; i++)
				destroy_stream(dice, AMDTP_IN_STREAM, i);
			goto end;
		}
	}

	err = amdtp_domain_init(&dice->domain);
	if (err < 0) {
		for (i = 0; i < MAX_STREAMS; ++i) {
			destroy_stream(dice, AMDTP_OUT_STREAM, i);
			destroy_stream(dice, AMDTP_IN_STREAM, i);
		}
	}
end:
	return err;
}