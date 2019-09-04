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
typedef  int /*<<< orphan*/  u32 ;
struct echoaudio {TYPE_1__* comm_page; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_2__ {int /*<<< orphan*/  sample_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_VC_UPDATE_CLOCKS ; 
 int EIO ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int set_sample_rate(struct echoaudio *chip, u32 rate)
{
	if (wait_handshake(chip))
		return -EIO;

	chip->sample_rate = rate;
	chip->comm_page->sample_rate = cpu_to_le32(rate);
	clear_handshake(chip);
	return send_vector(chip, DSP_VC_UPDATE_CLOCKS);
}