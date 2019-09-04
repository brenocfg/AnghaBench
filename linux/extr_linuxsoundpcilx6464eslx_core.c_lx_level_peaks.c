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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int* stat; int /*<<< orphan*/ * cmd; } ;
struct lx6464es {int /*<<< orphan*/  msg_lock; TYPE_1__ rmh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_12_GET_PEAK ; 
 int /*<<< orphan*/  PIPE_INFO_TO_CMD (int,int) ; 
 int /*<<< orphan*/  lx_message_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lx_message_send_atomic (struct lx6464es*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__* peak_map ; 

int lx_level_peaks(struct lx6464es *chip, int is_capture, int channels,
		   u32 *r_levels)
{
	int err = 0;
	int i;

	mutex_lock(&chip->msg_lock);
	for (i = 0; i < channels; i += 4) {
		u32 s0, s1, s2, s3;

		lx_message_init(&chip->rmh, CMD_12_GET_PEAK);
		chip->rmh.cmd[0] |= PIPE_INFO_TO_CMD(is_capture, i);

		err = lx_message_send_atomic(chip, &chip->rmh);

		if (err == 0) {
			s0 = peak_map[chip->rmh.stat[0] & 0x0F];
			s1 = peak_map[(chip->rmh.stat[0] >>  4) & 0xf];
			s2 = peak_map[(chip->rmh.stat[0] >>  8) & 0xf];
			s3 = peak_map[(chip->rmh.stat[0] >>  12) & 0xf];
		} else
			s0 = s1 = s2 = s3 = 0;

		r_levels[0] = s0;
		r_levels[1] = s1;
		r_levels[2] = s2;
		r_levels[3] = s3;

		r_levels += 4;
	}

	mutex_unlock(&chip->msg_lock);
	return err;
}