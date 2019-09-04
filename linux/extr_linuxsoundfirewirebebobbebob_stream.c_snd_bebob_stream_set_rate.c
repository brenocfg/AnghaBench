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
struct snd_bebob {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_GENERAL_PLUG_DIR_IN ; 
 int /*<<< orphan*/  AVC_GENERAL_PLUG_DIR_OUT ; 
 int avc_general_set_sig_fmt (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

int
snd_bebob_stream_set_rate(struct snd_bebob *bebob, unsigned int rate)
{
	int err;

	err = avc_general_set_sig_fmt(bebob->unit, rate,
				      AVC_GENERAL_PLUG_DIR_OUT, 0);
	if (err < 0)
		goto end;

	err = avc_general_set_sig_fmt(bebob->unit, rate,
				      AVC_GENERAL_PLUG_DIR_IN, 0);
	if (err < 0)
		goto end;

	/*
	 * Some devices need a bit time for transition.
	 * 300msec is got by some experiments.
	 */
	msleep(300);
end:
	return err;
}