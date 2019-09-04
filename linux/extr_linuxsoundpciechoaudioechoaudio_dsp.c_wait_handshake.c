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
struct echoaudio {TYPE_2__* card; TYPE_1__* comm_page; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ handshake; } ;

/* Variables and functions */
 int EBUSY ; 
 int HANDSHAKE_TIMEOUT ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_handshake(struct echoaudio *chip)
{
	int i;

	/* Wait up to 20ms for the handshake from the DSP */
	for (i = 0; i < HANDSHAKE_TIMEOUT; i++) {
		/* Look for the handshake value */
		barrier();
		if (chip->comm_page->handshake) {
			return 0;
		}
		udelay(1);
	}

	dev_err(chip->card->dev, "wait_handshake(): Timeout waiting for DSP\n");
	return -EBUSY;
}