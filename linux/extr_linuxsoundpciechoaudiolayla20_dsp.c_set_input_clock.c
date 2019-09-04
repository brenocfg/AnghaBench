#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct echoaudio {int input_clock; TYPE_1__* comm_page; TYPE_2__* card; scalar_t__ sample_rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  input_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_VC_UPDATE_CLOCKS ; 
#define  ECHO_CLOCK_INTERNAL 131 
#define  ECHO_CLOCK_SPDIF 130 
#define  ECHO_CLOCK_SUPER 129 
#define  ECHO_CLOCK_WORD 128 
 int EINVAL ; 
 int LAYLA20_CLOCK_INTERNAL ; 
 int LAYLA20_CLOCK_SPDIF ; 
 int LAYLA20_CLOCK_SUPER ; 
 int LAYLA20_CLOCK_WORD ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sample_rate (struct echoaudio*,scalar_t__) ; 

__attribute__((used)) static int set_input_clock(struct echoaudio *chip, u16 clock_source)
{
	u16 clock;
	u32 rate;

	rate = 0;
	switch (clock_source) {
	case ECHO_CLOCK_INTERNAL:
		rate = chip->sample_rate;
		clock = LAYLA20_CLOCK_INTERNAL;
		break;
	case ECHO_CLOCK_SPDIF:
		clock = LAYLA20_CLOCK_SPDIF;
		break;
	case ECHO_CLOCK_WORD:
		clock = LAYLA20_CLOCK_WORD;
		break;
	case ECHO_CLOCK_SUPER:
		clock = LAYLA20_CLOCK_SUPER;
		break;
	default:
		dev_err(chip->card->dev,
			"Input clock 0x%x not supported for Layla24\n",
			clock_source);
		return -EINVAL;
	}
	chip->input_clock = clock_source;

	chip->comm_page->input_clock = cpu_to_le16(clock);
	clear_handshake(chip);
	send_vector(chip, DSP_VC_UPDATE_CLOCKS);

	if (rate)
		set_sample_rate(chip, rate);

	return 0;
}