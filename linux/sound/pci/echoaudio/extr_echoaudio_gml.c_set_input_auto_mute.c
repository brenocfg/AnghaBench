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
struct echoaudio {int digital_in_automute; int /*<<< orphan*/  input_clock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int set_input_clock (struct echoaudio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_input_auto_mute(struct echoaudio *chip, int automute)
{
	dev_dbg(chip->card->dev, "set_input_auto_mute %d\n", automute);

	chip->digital_in_automute = automute;

	/* Re-set the input clock to the current value - indirectly causes
	the auto-mute flag to be sent to the DSP */
	return set_input_clock(chip, chip->input_clock);
}