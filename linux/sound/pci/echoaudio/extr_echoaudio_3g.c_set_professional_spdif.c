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
struct echoaudio {char professional_spdif; int /*<<< orphan*/  sample_rate; TYPE_1__* comm_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_frq_reg (struct echoaudio*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_spdif_bits (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_control_reg (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_professional_spdif(struct echoaudio *chip, char prof)
{
	u32 control_reg;

	control_reg = le32_to_cpu(chip->comm_page->control_register);
	chip->professional_spdif = prof;
	control_reg = set_spdif_bits(chip, control_reg, chip->sample_rate);
	return write_control_reg(chip, control_reg, get_frq_reg(chip), 0);
}