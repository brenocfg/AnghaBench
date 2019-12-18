#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int* stat; } ;
struct lx6464es {int freq_ratio; int /*<<< orphan*/  msg_lock; TYPE_1__ rmh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_01_GET_SYS_CFG ; 
 int FREQ_FIELD_OFFSET ; 
 int XES_FREQ_COUNT8_44_MAX ; 
 int XES_FREQ_COUNT8_44_MIN ; 
 int XES_FREQ_COUNT8_48_MAX ; 
 int XES_FREQ_COUNT8_MASK ; 
 int /*<<< orphan*/  lx_message_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lx_message_send_atomic (struct lx6464es*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int lx_dsp_get_clock_frequency(struct lx6464es *chip, u32 *rfreq)
{
	u16 ret = 0;
	u32 freq_raw = 0;
	u32 freq = 0;
	u32 frequency = 0;

	mutex_lock(&chip->msg_lock);

	lx_message_init(&chip->rmh, CMD_01_GET_SYS_CFG);
	ret = lx_message_send_atomic(chip, &chip->rmh);

	if (ret == 0) {
		freq_raw = chip->rmh.stat[0] >> FREQ_FIELD_OFFSET;
		freq = freq_raw & XES_FREQ_COUNT8_MASK;

		if ((freq < XES_FREQ_COUNT8_48_MAX) ||
		    (freq > XES_FREQ_COUNT8_44_MIN))
			frequency = 0; /* unknown */
		else if (freq >= XES_FREQ_COUNT8_44_MAX)
			frequency = 44100;
		else
			frequency = 48000;
	}

	mutex_unlock(&chip->msg_lock);

	*rfreq = frequency * chip->freq_ratio;

	return ret;
}