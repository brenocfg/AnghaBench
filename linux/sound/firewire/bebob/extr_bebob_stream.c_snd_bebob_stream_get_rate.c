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
 int EAGAIN ; 
 int avc_general_get_sig_fmt (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avc_general_set_sig_fmt (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
snd_bebob_stream_get_rate(struct snd_bebob *bebob, unsigned int *curr_rate)
{
	unsigned int tx_rate, rx_rate, trials;
	int err;

	trials = 0;
	do {
		err = avc_general_get_sig_fmt(bebob->unit, &tx_rate,
					      AVC_GENERAL_PLUG_DIR_OUT, 0);
	} while (err == -EAGAIN && ++trials < 3);
	if (err < 0)
		goto end;

	trials = 0;
	do {
		err = avc_general_get_sig_fmt(bebob->unit, &rx_rate,
					      AVC_GENERAL_PLUG_DIR_IN, 0);
	} while (err == -EAGAIN && ++trials < 3);
	if (err < 0)
		goto end;

	*curr_rate = rx_rate;
	if (rx_rate == tx_rate)
		goto end;

	/* synchronize receive stream rate to transmit stream rate */
	err = avc_general_set_sig_fmt(bebob->unit, rx_rate,
				      AVC_GENERAL_PLUG_DIR_IN, 0);
end:
	return err;
}