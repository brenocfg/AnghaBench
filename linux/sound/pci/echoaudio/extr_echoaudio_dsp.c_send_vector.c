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
struct echoaudio {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CHI32_VECTOR_BUSY ; 
 int /*<<< orphan*/  CHI32_VECTOR_REG ; 
 int EBUSY ; 
 int VECTOR_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_dsp_register (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dsp_register (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int send_vector(struct echoaudio *chip, u32 command)
{
	int i;

	wmb();	/* Flush all pending writes before sending the command */

	/* Wait up to 100ms for the "vector busy" bit to be off */
	for (i = 0; i < VECTOR_BUSY_TIMEOUT; i++) {
		if (!(get_dsp_register(chip, CHI32_VECTOR_REG) &
		      CHI32_VECTOR_BUSY)) {
			set_dsp_register(chip, CHI32_VECTOR_REG, command);
			/*if (i)  DE_ACT(("send_vector time: %d\n", i));*/
			return 0;
		}
		udelay(1);
	}

	dev_err(chip->card->dev, "timeout on send_vector\n");
	return -EBUSY;
}